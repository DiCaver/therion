/**
 * @file thtexfonts.cxx
 */
  
/* Copyright (C) 2003 Martin Budaj
 * 
 * $Date: $
 * $RCSfile: $
 * $Revision: $
 *
 * -------------------------------------------------------------------- 
 * This program is free software; you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation; either version 2 of the License, or
 * any later version.
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 * 
 * You should have received a copy of the GNU General Public License
 * along with this program; if not, write to the Free Software
 * Foundation, Inc., 59 Temple Place, Suite 330, Boston, MA  02111-1307  USA
 * --------------------------------------------------------------------
 */

#include <string>
#include <list>
#include <sstream>
#include <fstream>
#include <iostream>

#include <cstring>
#include <cstdio>

#include "thtexfonts.h"
#include "thtexenc.cxx"
#include "thpdfdbg.h"

#ifndef NOTHERION
#include "thbuffer.h"
thbuffer thtexfontsbuff;
#endif

using namespace std;

list<fontrecord> FONTS;
typedef list<int> unistr;

// returns the index of given encoding (as used in predefined encoding arrays)
// or -1 if such an encoding is not known

int get_enc_id(char* enc) {
  for (int i=0; i<max_enc; i++) if (strcmp(encodings[i],enc) == 0) return i;
  return -1;
}

void print_tex_encodings (void) {
  for (int i=0; i<max_enc; i++) cout << encodings[i] << endl;
}

void init_encodings() {
  fontrecord F;
  F.id = get_enc_id("raw");
  F.rm = "cmr10";
  F.it = "cmti10";
  F.bf = "cmbx10";
  F.ss = "cmss10";
  F.si = "cmssi10";
  FONTS.push_back(F);
  F.id = get_enc_id("xl2");
  F.rm = "csr10";
  F.it = "csti10";
  F.bf = "csbx10";
  F.ss = "csss10";
  F.si = "csssi10";
  FONTS.push_back(F);
}

unistr utf2uni(string s) {
  unsigned char c;
  unistr t;
  int j;

  for (unsigned i=0; i<s.size(); i++) {
    c = s[i];
    if (c<128) {
      t.push_back(c);
    }
    else if (c>=192 && c<=223) {
      j = 64*(c-192); 
      c = s[++i];
      j += c-128;
      t.push_back(j);
    }
    else if (c>=224 && c<=239) {
      j = 4096*(c-224);
      c = s[++i];
      j += 64*(c-128); 
      c = s[++i];
      j += c-128;
      t.push_back(j);
    }
    else therror (("Invalid utf-8 string!")); // we don't support higher
                                              // unicode characters
  }
  return t;
}

// converts utf8 to 2B Unicode in a special format for pdfTeX

string utf2texoctal(string str) {
  unistr s = utf2uni(str);
  string t;
  char ch[10];
//  t = "\\ne\\376\\ne\\377";
  unsigned char c;
  for (unistr::iterator I = s.begin(); I != s.end(); I++) {
    c = (*I) / 256;
    sprintf(ch,"%o",c);
    t = t + "\\ne\\" + (string) ch;
    c = (*I) % 256;
    sprintf(ch,"%o",c);
    t = t + "\\ne\\" + (string) ch;
  }
  return t;
}

// converts utf8 to 2B Unicode in a special format for pdfTeX

string utf2texhex(string str) {
  unistr s = utf2uni(str);
  string t;
  char ch[10];
  unsigned char c;
  for (unistr::iterator I = s.begin(); I != s.end(); I++) {
    c = (*I) / 256;
    sprintf(ch,"%02x",c);
    t += (string) ch;
    c = (*I) % 256;
    sprintf(ch,"%02x",c);
    t += (string) ch;
  }
  return t;
}

// main task is done here

string utf2tex(string str) {
  unistr s = utf2uni(str);
  ostringstream T;
  string tmp;
  int wc;  //wide char
  int lastenc = -1;
  int align = 0;
  bool is_multiline = false;

  if (str.find("<center>") != string::npos) align = 1;
  else if (str.find("<left>") != string::npos) align = 0;
  else if (str.find("<right>") != string::npos) align = 2;

  if (str.find("<br>") != string::npos) is_multiline = true;
  
  if (is_multiline) {
    T << "\\vbox{\\halign{";
    if (align > 0) T << "\\hfil";
    T << "#";
    if (align < 2) T << "\\hfil";
    T << "\\cr";
  }
  
  for (unistr::iterator I = s.begin(); I != s.end(); I++) {
    wc = *I;
    if (wc == 32) {                     // space requires special treatment 
      T << " ";                         // (it's not included in TeX fonts)
      continue;                         // so encodings search doesn't help
    }
    else if (wc == 60) {                // special <.> string formatting
      tmp = "";
      I++;
      while (I != s.end() && (wc = *I) != 62 && wc < 128) {
        tmp += char(wc);
        I++;
      }
      if (tmp == "br") T << "\\cr ";
      else if (tmp == "center" || tmp == "left" || tmp == "right") ;
      else T << "?";
      if (I == s.end()) break;   // incorrect input (no closing `>')
      continue;
    }
    bool local_exit = false;
    bool local_repeat = true;

    while(local_repeat) {
      local_repeat = false;
      for (list<fontrecord>::iterator J = FONTS.begin(); J != FONTS.end(); J++) {
        int j = J->id;
        for (int i=0; i<256; i++) {
          if (texenc[i][j] == wc) {
            if (j != lastenc) {           // do a better optimization
                                          // of the font changes in a string
              T << "\\thf" << u2str(j+1) << " ";
              lastenc = j;
            }
                           // some characters require special treatment in TeX
            if (i==0 || i==127 || i==123 || i==125 || i==36 || i==38 || 
                i==10 || i==35 || i==95 || i==126 || i==13 || i==94 || 
                i==92 || i==37) {
              T << "\\char" << i << " ";
            }
            else {
              T << char(i);
            }
            local_exit = true;
            local_repeat = false;
          }
          if (local_exit) break;
        }
        if (local_exit) break;
      }
      if (!local_exit) {

        // current character is not included in any of the used encodings;
        // let's try to find an approximation based on Unicode
        // decomposition table

        int a = 0, b = max_base - 1, i, j;
        while (a<=b) {
          i = (int) (a+b)/2;
          j = unibase[i][0];
          if (j == wc) {
            wc = unibase[i][1];
            local_repeat = true;
            break;
          }
          if (j > wc) 
            b = i - 1;
          else
            a = i + 1;
        } 
      }
    }
    if (!local_exit)       // we didn't find anything to display
    
      // it would be possible to add here various characters mapped
      // by plain TeX macros to mathematical fonts (backslash &c.)
      // This would require to make math fonts scalable with the \size[.] macro
    
      T << "?";
  }
  
  if (is_multiline) {
    T << "\\cr}}";
  }
  
  return T.str();
}

//const char * utf2tex (char * s) {
//  string t = utf2tex(string(s));
//  return t.c_str();
//}

#ifndef NOTHERION
const char * utf2tex (char * s) {
  string t = utf2tex(string(s));
  thtexfontsbuff.strcpy(t.c_str());
  return thtexfontsbuff.get_buffer();
}
#endif

// For simlicity we suppose that all characters which are set by TeX macros
// are included in the first encoding specified. This concerns especially 
// page numbers, labels, and scalebar legend. Therefore we switch to \thfa
// after each size/style change

void print_fonts_setup() {
  ofstream P("th_enc.tex");
  if(!P) therror(("Can't write file"));
  P << "\\def\\rms{\\rm}" << endl;
  P << "\\def\\its{\\it}" << endl;
  P << "\\def\\bfs{\\bf}" << endl;
  P << "\\def\\sss{\\ss}" << endl;
  P << "\\def\\sis{\\si}" << endl;

  P << "\\def\\size[#1]{%" << endl;
  P << "  \\let\\prevstyle\\laststyle" << endl;
  P << "  \\baselineskip#1pt" << endl;
  P << "  \\baselineskip=1.2\\baselineskip" << endl;

  string firstfont = "\\thf" + u2str(FONTS.begin()->id+1);

  P << "  \\def\\rm{";
  for (list<fontrecord>::iterator J = FONTS.begin(); J != FONTS.end(); J++)
    P << "\\font\\thf" << u2str(J->id+1) << "=" << J->rm << " at#1pt";
  P << "\\let\\laststyle\\rms" << firstfont << "}%" << endl;

  P << "  \\def\\it{";
  for (list<fontrecord>::iterator J = FONTS.begin(); J != FONTS.end(); J++)
    P << "\\font\\thf" << u2str(J->id+1) << "=" << J->it << " at#1pt";
  P << "\\let\\laststyle\\its" << firstfont << "}%" << endl;

  P << "  \\def\\bf{";
  for (list<fontrecord>::iterator J = FONTS.begin(); J != FONTS.end(); J++)
    P << "\\font\\thf" << u2str(J->id+1) << "=" << J->bf << " at#1pt";
  P << "\\let\\laststyle\\bfs" << firstfont << "}%" << endl;

  P << "  \\def\\ss{";
  for (list<fontrecord>::iterator J = FONTS.begin(); J != FONTS.end(); J++)
    P << "\\font\\thf" << u2str(J->id+1) << "=" << J->ss << " at#1pt";
  P << "\\let\\laststyle\\sss" << firstfont << "}%" << endl;

  P << "  \\def\\si{";
  for (list<fontrecord>::iterator J = FONTS.begin(); J != FONTS.end(); J++)
    P << "\\font\\thf" << u2str(J->id+1) << "=" << J->si << " at#1pt";
  P << "\\let\\laststyle\\sis" << firstfont << "}%" << endl;
  
  P << "  \\prevstyle" << endl;
  P << "}";
  P << "\\let\\laststyle\\rms" << endl;
  P << "\\size[10]\\ss" << endl;
  P.close();
}


#ifdef NOTHERION
#ifndef NOMAIN
int main () {
//cout << "xl2 " << get_enc_index("xl2") << endl;
  return(0);
}
#endif
#endif

