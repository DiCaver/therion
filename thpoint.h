/**
 * @file thpoint.h
 * point module.
 */
  
/* Copyright (C) 2000 Stacho Mudrak
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
 
#ifndef thpoint_h
#define thpoint_h


#include "th2ddataobject.h"
#include "thparse.h"
#include "thdb2dpt.h"

/**
 * point command options tokens.
 */
 
enum {
  TT_POINT_UNKNOWN = 3000,
  TT_POINT_TYPE = 3001,
  TT_POINT_SUBTYPE = 3002,
  TT_POINT_STATION = 3003,
  TT_POINT_EXTEND = 3004,
  TT_POINT_ORIENT = 3005,
  TT_POINT_XSIZE = 3006,
  TT_POINT_YSIZE = 3007,
  TT_POINT_SIZE = 3008,
  TT_POINT_ALIGN = 3009,
  TT_POINT_VALUE = 3010,
  TT_POINT_TEXT = 3011,
  TT_POINT_SCRAP = 3012,
};


/**
 * point command options parsing table.
 */
 
static const thstok thtt_point_opt[] = {
  {"align", TT_POINT_ALIGN},
  {"extend", TT_POINT_EXTEND},
  {"name", TT_POINT_STATION},
  {"orient", TT_POINT_ORIENT},
  {"orientation", TT_POINT_ORIENT},
  {"scrap", TT_POINT_SCRAP},
  {"size", TT_POINT_SIZE},
  {"subtype", TT_POINT_SUBTYPE},
  {"text", TT_POINT_TEXT},
  {"value", TT_POINT_VALUE},
  {"x-size", TT_POINT_XSIZE},
  {"y-size", TT_POINT_YSIZE},
  {NULL, TT_POINT_UNKNOWN},
};

/**
 * Special point tags.
 */

enum {
// height (passage) tags
  TT_POINT_TAG_HEIGHT_U = 1,
  TT_POINT_TAG_HEIGHT_P = 2,
  TT_POINT_TAG_HEIGHT_N = 4,
  TT_POINT_TAG_HEIGHT_UQ = 8,
  TT_POINT_TAG_HEIGHT_PQ = 16,
  TT_POINT_TAG_HEIGHT_NQ = 32,
  TT_POINT_TAG_HEIGHT_ALL = TT_POINT_TAG_HEIGHT_U |
    TT_POINT_TAG_HEIGHT_P | TT_POINT_TAG_HEIGHT_N |
    TT_POINT_TAG_HEIGHT_UQ |
    TT_POINT_TAG_HEIGHT_PQ | TT_POINT_TAG_HEIGHT_NQ,

// date
  TT_POINT_TAG_DATE = 1,
  
};


/**
 * Point types tokens.
 */

enum {
  TT_POINT_TYPE_UNKNOWN,

// specialne typy
  TT_POINT_TYPE_STATION,
  TT_POINT_TYPE_SECTION,
  TT_POINT_TYPE_WATER_FLOW,
  TT_POINT_TYPE_SPRING,
  TT_POINT_TYPE_SINK,
  TT_POINT_TYPE_LABEL,
  TT_POINT_TYPE_REMARK,
  TT_POINT_TYPE_ALTITUDE,
  TT_POINT_TYPE_HEIGHT,
  TT_POINT_TYPE_PASSAGE_HEIGHT,
  TT_POINT_TYPE_STATION_NAME,
  TT_POINT_TYPE_DATE,
  TT_POINT_TYPE_AIR_DRAUGHT,
  TT_POINT_TYPE_ENTRANCE,
  TT_POINT_TYPE_GRADIENT,
  
// vystroj
  TT_POINT_TYPE_NO_EQUIPEMENT,
  TT_POINT_TYPE_ANCHOR,
  TT_POINT_TYPE_ROPE,
  TT_POINT_TYPE_FIXED_LADDER,
  TT_POINT_TYPE_ROPE_LADDER,
  TT_POINT_TYPE_STEPS,
  TT_POINT_TYPE_BRIDGE,
  TT_POINT_TYPE_TRAVERSE,
  TT_POINT_TYPE_CAMP,

// ukoncenia chodby
  TT_POINT_TYPE_CONTINUATION,
  TT_POINT_TYPE_NARROW_END,
  TT_POINT_TYPE_LOW_END,
  TT_POINT_TYPE_FLOWSTONE_CHOKE,
  TT_POINT_TYPE_BREAKDOWN_CHOKE,

// vypln
  TT_POINT_TYPE_FLOWSTONE,
  TT_POINT_TYPE_MOONMILK,
  TT_POINT_TYPE_STALACTITE,
  TT_POINT_TYPE_STALAGMITE,
  TT_POINT_TYPE_PILLAR,
  TT_POINT_TYPE_CURTAIN,
  TT_POINT_TYPE_HELECTITE,
  TT_POINT_TYPE_SODA_STRAW,
  TT_POINT_TYPE_CRYSTAL,
  TT_POINT_TYPE_WALL_CALCITE,
  TT_POINT_TYPE_POPCORN,
  TT_POINT_TYPE_DISK,
  TT_POINT_TYPE_GYPSUM,
  TT_POINT_TYPE_GYPSUM_FLOWER,
  TT_POINT_TYPE_ARAGONITE,
  TT_POINT_TYPE_CAVE_PEARL,
  TT_POINT_TYPE_RIMSTONE_POOL,
  TT_POINT_TYPE_ROMSTONE_DAM,
  TT_POINT_TYPE_ANASTOMOSIS,
  TT_POINT_TYPE_KARREN,
  TT_POINT_TYPE_SCALLOP,
  TT_POINT_TYPE_FLUTE,
  TT_POINT_TYPE_RAFT_CONE,
  
// plosne vyplne
  TT_POINT_TYPE_BEDROCK,
  TT_POINT_TYPE_SAND,
  TT_POINT_TYPE_RAFT,
  TT_POINT_TYPE_CLAY,
  TT_POINT_TYPE_PEBBLES,
  TT_POINT_TYPE_DEBRIS,
  TT_POINT_TYPE_BLOCKS,
  TT_POINT_TYPE_WATER,
  TT_POINT_TYPE_ICE,
  TT_POINT_TYPE_GUANO,

// ina vypln
  TT_POINT_TYPE_ARCHEO_MATERIAL,
  TT_POINT_TYPE_PALEO_MATERIAL,
  TT_POINT_TYPE_VEGETABLE_DEBRIS,
  TT_POINT_TYPE_ROOT,

};


/**
 * Point types parsing table.
 */
 
static const thstok thtt_point_types[] = {
  {"air-draught",TT_POINT_TYPE_AIR_DRAUGHT},
  {"altitude",TT_POINT_TYPE_ALTITUDE},
  {"anchor",TT_POINT_TYPE_ANCHOR},
  {"anastomosis",TT_POINT_TYPE_ANASTOMOSIS},
  {"aragonite",TT_POINT_TYPE_ARAGONITE},
  {"archeo-material",TT_POINT_TYPE_ARCHEO_MATERIAL},
  {"bedrock",TT_POINT_TYPE_BEDROCK},
  {"blocks",TT_POINT_TYPE_BLOCKS},
  {"breakdown-choke",TT_POINT_TYPE_BREAKDOWN_CHOKE},
  {"bridge",TT_POINT_TYPE_BRIDGE},
  {"camp",TT_POINT_TYPE_CAMP},
  {"cave-pearl",TT_POINT_TYPE_CAVE_PEARL},
  {"clay",TT_POINT_TYPE_CLAY},
  {"continuation",TT_POINT_TYPE_CONTINUATION},
  {"crystal",TT_POINT_TYPE_CRYSTAL},
  {"curtain",TT_POINT_TYPE_CURTAIN},
  {"date",TT_POINT_TYPE_DATE},
  {"debris",TT_POINT_TYPE_DEBRIS},
  {"disk",TT_POINT_TYPE_DISK},
  {"entrance",TT_POINT_TYPE_ENTRANCE},
  {"fixed-ladder",TT_POINT_TYPE_FIXED_LADDER},
  {"flowstone",TT_POINT_TYPE_FLOWSTONE},
  {"flowstone-choke",TT_POINT_TYPE_FLOWSTONE_CHOKE},
  {"flute",TT_POINT_TYPE_FLUTE},
  {"gradient",TT_POINT_TYPE_GRADIENT},
  {"guano",TT_POINT_TYPE_GUANO},
  {"gypsum",TT_POINT_TYPE_GYPSUM},
  {"gypsum-flower",TT_POINT_TYPE_GYPSUM_FLOWER},
  {"height",TT_POINT_TYPE_HEIGHT},
  {"helectite",TT_POINT_TYPE_HELECTITE},
  {"ice",TT_POINT_TYPE_ICE},
  {"karren",TT_POINT_TYPE_KARREN},
  {"label",TT_POINT_TYPE_LABEL},
  {"low-end",TT_POINT_TYPE_LOW_END},
  {"moonmilk",TT_POINT_TYPE_MOONMILK},
  {"narrow-end",TT_POINT_TYPE_NARROW_END},
  {"no-equipement",TT_POINT_TYPE_NO_EQUIPEMENT},
  {"paleo-material",TT_POINT_TYPE_PALEO_MATERIAL},
  {"passage-height",TT_POINT_TYPE_PASSAGE_HEIGHT},
  {"pebbles",TT_POINT_TYPE_PEBBLES},
  {"pillar",TT_POINT_TYPE_PILLAR},
  {"popcorn",TT_POINT_TYPE_POPCORN},
  {"raft",TT_POINT_TYPE_RAFT},
  {"raft-cone",TT_POINT_TYPE_RAFT_CONE},
  {"remark",TT_POINT_TYPE_REMARK},
  {"rimstone-dam",TT_POINT_TYPE_ROMSTONE_DAM},
  {"rimstone-pool",TT_POINT_TYPE_RIMSTONE_POOL},
  {"root",TT_POINT_TYPE_ROOT},
  {"rope",TT_POINT_TYPE_ROPE},
  {"rope-ladder",TT_POINT_TYPE_ROPE_LADDER},
  {"sand",TT_POINT_TYPE_SAND},
  {"scallop",TT_POINT_TYPE_SCALLOP},
  {"section",TT_POINT_TYPE_SECTION},
  {"sink",TT_POINT_TYPE_SINK},
  {"soda-straw",TT_POINT_TYPE_SODA_STRAW},
  {"spring",TT_POINT_TYPE_SPRING},
  {"stalactite",TT_POINT_TYPE_STALACTITE},
  {"stalagmite",TT_POINT_TYPE_STALAGMITE},
  {"station", TT_POINT_TYPE_STATION},
  {"station-name", TT_POINT_TYPE_STATION_NAME},
  {"steps",TT_POINT_TYPE_STEPS},
  {"traverse",TT_POINT_TYPE_TRAVERSE},
  {"vegetable-debris",TT_POINT_TYPE_VEGETABLE_DEBRIS},
  {"wall-calcite",TT_POINT_TYPE_WALL_CALCITE},
  {"water",TT_POINT_TYPE_WATER},
  {"water-flow",TT_POINT_TYPE_WATER_FLOW},
	{NULL, TT_POINT_TYPE_UNKNOWN},
};

/**
 * Point align tokens.
 */

enum {
  TT_POINT_ALIGN_UNKNOWN,
  TT_POINT_ALIGN_T,
  TT_POINT_ALIGN_B,
  TT_POINT_ALIGN_L,
  TT_POINT_ALIGN_R,
  TT_POINT_ALIGN_TL,
  TT_POINT_ALIGN_BL,
  TT_POINT_ALIGN_TR,
  TT_POINT_ALIGN_BR,
  TT_POINT_ALIGN_C,
};


/**
 * Point align parsing table.
 */
 
static const thstok thtt_point_aligns[] = {
  {"b", TT_POINT_ALIGN_B},
  {"bl", TT_POINT_ALIGN_BL},
  {"bottom", TT_POINT_ALIGN_B},
  {"bottom-left", TT_POINT_ALIGN_BL},
  {"bottom-right", TT_POINT_ALIGN_BR},
  {"br", TT_POINT_ALIGN_BR},
  {"c", TT_POINT_ALIGN_C},
  {"center", TT_POINT_ALIGN_C},
  {"l", TT_POINT_ALIGN_L},
  {"left", TT_POINT_ALIGN_L},
  {"r", TT_POINT_ALIGN_R},
  {"right", TT_POINT_ALIGN_R},
  {"t", TT_POINT_ALIGN_T},
  {"tl", TT_POINT_ALIGN_TL},
  {"top", TT_POINT_ALIGN_T},
  {"top-left", TT_POINT_ALIGN_TL},
  {"top-right", TT_POINT_ALIGN_TR},
  {"tr", TT_POINT_ALIGN_TR},
	{NULL, TT_POINT_ALIGN_UNKNOWN},
};




/**
 * Point subtypes tokens.
 */

enum {
  TT_POINT_SUBTYPE_UNKNOWN,
  TT_POINT_SUBTYPE_TEMP,
  TT_POINT_SUBTYPE_PAINTED,
  TT_POINT_SUBTYPE_FIXED,
  TT_POINT_SUBTYPE_NATURAL,
  TT_POINT_SUBTYPE_PALEO,
  TT_POINT_SUBTYPE_PERMANENT,
  TT_POINT_SUBTYPE_INTERMITTENT,
};


/**
 * Point types parsing table.
 */
 
static const thstok thtt_point_subtypes[] = {
  {"fixed", TT_POINT_SUBTYPE_FIXED},
  {"intermittent", TT_POINT_SUBTYPE_INTERMITTENT},
  {"natural", TT_POINT_SUBTYPE_NATURAL},
  {"painted", TT_POINT_SUBTYPE_PAINTED},
  {"paleo", TT_POINT_SUBTYPE_PALEO},
  {"permanent", TT_POINT_SUBTYPE_PERMANENT},
  {"temporary", TT_POINT_SUBTYPE_TEMP},
	{NULL, TT_POINT_SUBTYPE_UNKNOWN},
};


/**
 * Extend options.
 */
 
enum {
  TT_POINT_EXTEND_NONE = 0,
  TT_POINT_EXTEND_STICKYON = 1,
  TT_POINT_EXTEND_STICKYOFF = 2,
  TT_POINT_EXTEND_STICKY = 3,
  TT_POINT_EXTEND_LEFT = 4,
  TT_POINT_EXTEND_RIGHT = 8,
  TT_POINT_EXTEND_ROOT = 16,
  TT_POINT_EXTEND_PREV = 17,
};



/**
 * Extend options parsing table.
 */
 
static const thstok thtt_point_extopt[] = {
  {"left", TT_POINT_EXTEND_LEFT},
  {"prev", TT_POINT_EXTEND_PREV},
  {"previous", TT_POINT_EXTEND_PREV},
  {"right", TT_POINT_EXTEND_RIGHT},
  {"root", TT_POINT_EXTEND_ROOT},
  {"sticky", TT_POINT_EXTEND_STICKY},
	{NULL, TT_POINT_EXTEND_NONE},
};



/**
 * point class.
 */

class thpoint : public th2ddataobject {

  public:
  
  friend class thdb2d;

  int type,  ///< Point type.
    subtype,  ///< Point subtype.
    align;  ///< Point align.
  double orient, xsize, ysize;  ///<...
  
  char * text;  ///< Point text.
    
  thdb2dpt * point;  ///< Point coordinates.
  
  class thdb2dcp * cpoint; ///< Control point.
  
  thobjectname station_name,  ///< Station name.
    extend_name;  ///< Extend name.
  thpoint * extend_point;  ///< Extend previous point.
  char extend_opts;  ///< Extend options.
    
  void parse_type(char * tstr);  ///< Parse point type.

  void parse_align(char * tstr);  ///< Parse point align.
  
  void parse_subtype(char * ststr);  ///< Parse point subtype.
  
  void parse_extend(char * estr);  ///< Parse station extend.

  void parse_text(char * ss);  ///< Parse point text.

  void parse_value(char * ss);  ///< Parse point value.

  /**
   * Standard constructor.
   */
  
  thpoint();
  
  
  /**
   * Standard destructor.
   */
   
  ~thpoint();
  
  
  /**
   * Return class identifier.
   */
  
  virtual int get_class_id();
  
  
  /**
   * Return class name.
   */
   
  virtual char * get_class_name() {return "thpoint";};
  
  
  /**
   * Return true, if son of given class.
   */
  
  virtual bool is(int class_id);
  
  
  /**
   * Return number of command arguments.
   */
   
  virtual int get_cmd_nargs();
  
  
  /**
   * Return command name.
   */
   
  virtual char * get_cmd_name();
  
  
  /**
   * Return command end option.
   */
   
  virtual char * get_cmd_end();
  
  
  /**
   * Return option description.
   */
   
  virtual thcmd_option_desc get_cmd_option_desc(char * opts);
  
  
  /**
   * Set command option.
   *
   * @param cod Command option description.
   * @param args Option arguments arry.
   * @param argenc Arguments encoding.
   */
   
  virtual void set(thcmd_option_desc cod, char ** args, int argenc, unsigned long indataline);


  /**
   * Delete this object.
   *
   * @warn Always use this methos instead of delete function.
   */
   
  virtual void self_delete();


  /**
   * Print object properties.
   */
   
  virtual void self_print_properties(FILE * outf); 

  /**
   * Export to metapost file.
   */
   
  virtual void export_mp(class thexpmapmpxs * out);
  
};

#endif

