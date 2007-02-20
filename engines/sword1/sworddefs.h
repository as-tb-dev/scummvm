/* ScummVM - Scumm Interpreter
 * Copyright (C) 2003-2006 The ScummVM project
 *
 * This program is free software; you can redistribute it and/or
 * modify it under the terms of the GNU General Public License
 * as published by the Free Software Foundation; either version 2
 * of the License, or (at your option) any later version.

 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.

 * You should have received a copy of the GNU General Public License
 * along with this program; if not, write to the Free Software
 * Foundation, Inc., 51 Franklin Street, Fifth Floor, Boston, MA 02110-1301, USA.
 *
 * $URL$
 * $Id$
 *
 */

#ifndef SWORD1_SWORDDEFS_H
#define SWORD1_SWORDDEFS_H

#include "common/scummsys.h"

namespace Sword1 {

#define LOOPED 1

#define	FRAME_RATE			12						// number of frames per second (max rate)
#define	SCREEN_WIDTH		640
#define	SCREEN_DEPTH		400
#define	SCREEN_LEFT_EDGE	128
#define	SCREEN_RIGHT_EDGE	(128+SCREEN_WIDTH-1)
#define	SCREEN_TOP_EDGE		128
#define	SCREEN_BOTTOM_EDGE	(128+SCREEN_DEPTH-1)
#define TYPE_FLOOR 1
#define TYPE_MOUSE 2
#define TYPE_SPRITE 3
#define TYPE_NON_MEGA 4
#define TYPE_MEGA 5
#define TYPE_PLAYER 6
#define TYPE_TEXT 7
#define STAT_MOUSE 1
#define STAT_LOGIC 2
#define STAT_EVENTS 4
#define STAT_FORE 8
#define STAT_BACK 16
#define STAT_SORT 32
#define STAT_SHRINK 64
#define STAT_BOOKMARK 128
#define STAT_TALK_WAIT 256
#define STAT_OVERRIDE 512

#define LOGIC_idle 0
#define LOGIC_script 1
#define LOGIC_AR_animate 2
#define LOGIC_interaction 3
#define LOGIC_speech 4
#define LOGIC_full_anim 5
#define LOGIC_anim 6
#define LOGIC_pause 7
#define LOGIC_wait_for_sync 8
#define LOGIC_quit 9
#define LOGIC_restart 10
#define LOGIC_bookmark 11
#define LOGIC_wait_for_talk 12
#define LOGIC_start_talk 13
#define LOGIC_choose 14
#define LOGIC_new_script 15
#define LOGIC_pause_for_event 16

#define SCRIPT_CONT 1
#define SCRIPT_STOP 0

#define INS_talk 1

#define TOTAL_pockets 52
#define TOTAL_subjects (375-256+1)
#define BASE_SUBJECT 256

#define TOTAL_SECTIONS		150						//number of sections, rooms + mega sections
#define	TOTAL_ROOMS			100						//total number of rooms
#define	ITM_PER_SEC			0x10000					//65536 items per section -> was originally called "SIZE"
#define	ITM_ID				0xFFFF					//& with this -> originally "NuSIZE"

#define	MAX_text_obs	2			//text compacts
#define	TEXT_sect		149			//text compacts exist in section 149, probably after all the megas

#include "common/pack-start.h"	// START STRUCT PACKING

struct Header {
	char type[6];
	uint16 version;
	uint32	comp_length;
	char	compression[4];
	uint32	decomp_length;
};

struct FrameHeader {
	uint8 runTimeComp[4];
	uint32 compSize;
	uint16 width;
	uint16 height;
	int16 offsetX;
	int16 offsetY;
};

struct ParallaxHeader {
	char type[16];
	uint16 sizeX;
	uint16 sizeY;
};

struct AnimUnit {
	uint32 animX;
	uint32 animY;
	uint32 animFrame;
};

struct AnimSet {
	uint32 cdt;
	uint32 spr;
};

struct WalkGridHeader {
	int32 scaleA;
	int32 scaleB;
	int32 numBars;
	int32 numNodes;
};

#include "common/pack-end.h"	// END STRUCT PACKING

enum fileTypes {
	TYPE_CD1 = 0,
	TYPE_CD2,
	TYPE_DEMO,
	TYPE_IMMED,
	TYPE_SPEECH1,
	TYPE_SPEECH2
};

enum fileFlags {
	FLAG_CD1 =		(1 << TYPE_CD1),	  // this file is on cd1
	FLAG_CD2 =		(1 << TYPE_CD2),	  // this file is on cd2
	FLAG_DEMO =		(1 << TYPE_DEMO),	  // file for the demo version
	FLAG_IMMED =	(1 << TYPE_IMMED),	  // this file is needed immediately, game won't start without it
	FLAG_SPEECH1 =	(1 << TYPE_SPEECH1),
	FLAG_SPEECH2 =	(1 << TYPE_SPEECH2)
};

struct CdFile {
	const char *name;
	uint8 flags;
};

enum Language {
	BS1_ENGLISH = 0,
	BS1_FRENCH,
	BS1_GERMAN,
	BS1_ITALIAN,
	BS1_SPANISH,
	BS1_CZECH,
	BS1_PORT
};

#define SAM		2162689
#define PLAYER	8388608
#define GEORGE	8388608
#define NICO	8454144
#define BENOIR	8585216
#define ROSSO	8716288
#define DUANE	8781824
#define MOUE	9502720
#define ALBERT	9568256

#define STAND		0
#define UP			0
#define UP_RIGHT	1
#define U_R			1
#define RIGHT		2
#define DOWN_RIGHT	3
#define D_R			3
#define DOWN		4
#define DOWN_LEFT	5
#define D_L			5
#define LEFT		6
#define UP_LEFT		7
#define U_L			7

#define BEER_TOWEL 3
#define HOTEL_KEY 4
#define BALL 5
#define RED_NOSE 7
#define POLISHED_CHALICE 8
#define PHOTOGRAPH 10
#define GEM 13
#define LAB_PASS 17
#define LIFTING_KEYS 18
#define MANUSCRIPT 19
#define PLASTER 23
#define ROSSO_CARD 27
#define TISSUE 32
#define LENS 37
#define TRIPOD 36
#define CHALICE 31
#define MATCHBOOK 20
#define PRESSURE_GAUGE 24
#define BUZZER 26
#define TOILET_KEY 28
#define STONE_KEY 30
#define TOILET_BRUSH 33
#define MIRROR 38
#define TOWEL_CUT 39

#define SC58_PATH_X 225
#define SC58_PATH_Y 369

#define FLOOR_1 65536
#define FLOOR_2 131072
#define FLOOR_3 196608
#define FLOOR_4 262144
#define FLOOR_5 327680
#define FLOOR_6 393216
#define FLOOR_7 458752
#define FLOOR_8 524288
#define FLOOR_9 589824
#define FLOOR_10 655360
#define FLOOR_11 720896
#define FLOOR_12 786432
#define FLOOR_13 851968
#define FLOOR_14 917504
#define FLOOR_15 983040
#define FLOOR_16 1048576
#define FLOOR_17 1114112
#define FLOOR_18 1179648
#define FLOOR_19 1245184
#define FLOOR_20 1310720
#define FLOOR_21 1376256
#define FLOOR_22 1441792
#define FLOOR_23 1507328
#define FLOOR_24 1572864
#define FLOOR_25 1638400
#define FLOOR_26 1703936
#define FLOOR_27 1769472
#define FLOOR_28 1835008
#define FLOOR_29 1900544
#define FLOOR_31 2031616
#define FLOOR_32 2097152
#define FLOOR_33 2162688
#define FLOOR_34 2228224
#define FLOOR_35 2293760
#define FLOOR_36 2359296
#define FLOOR_37 2424832
#define FLOOR_38 2490368
#define FLOOR_39 2555904
#define FLOOR_40 2621440
#define FLOOR_41 2686976
#define FLOOR_42 2752512
#define FLOOR_43 2818048
#define FLOOR_45 2949120
#define FLOOR_46 3014656
#define FLOOR_47 3080192
#define FLOOR_48 3145728
#define FLOOR_49 3211264
#define FLOOR_50 3276800
#define FLOOR_53 3473408
#define FLOOR_54 3538944
#define FLOOR_55 3604480
#define FLOOR_56 3670016
#define FLOOR_57 3735552
#define FLOOR_58 3801088
#define FLOOR_59 3866624
#define FLOOR_60 3932160
#define LEFT_FLOOR_61 3997697
#define FLOOR_62 4063232
#define FLOOR_63 4128768
#define FLOOR_65 4259840
#define FLOOR_66 4325376
#define FLOOR_67 4390912
#define FLOOR_69 4521984
#define RIGHT_FLOOR_71 4653060
#define FLOOR_72 4718592
#define FLOOR_73 4784128
#define FLOOR_74 4849664
#define FLOOR_75 4915200
#define FLOOR_76 4980736
#define FLOOR_77 5046272
#define FLOOR_78 5111808
#define FLOOR_79 5177344
#define FLOOR_80 5242880
#define FLOOR_86 5636096
#define FLOOR_91 5963776
#define FLOOR_99 6488064


#define menu_bible 69
#define menu_newspaper 1
#define menu_hazel_wand 2
#define menu_beer_towel 68
#define menu_beer_towel_wet 4
#define menu_beer_towel_damp 5
#define menu_beer_towel_dried 6
#define menu_hotel_key 7
#define menu_ball 8
#define menu_statuette 9
#define menu_red_nose_first 10
#define menu_red_nose_second 11
#define menu_polished_chalice 12
#define menu_dollar_bill 13
#define menu_photograph 14
#define menu_keyring_first 15
#define menu_keyring_second 70
#define menu_keyring_third 17
#define menu_fuse_wire 18
#define menu_gem 19
#define menu_statuette_paint 20
#define menu_stick 21
#define menu_excav_key 71
#define menu_false_key 72
#define menu_painted_key 73
#define menu_lab_pass 25
#define menu_lifting_keys 26
#define menu_manuscript 27
#define menu_match_book 28
#define menu_suit_material 29
#define menu_stick_towel 30
#define menu_plaster 31
#define menu_pressure_gauge 32
#define menu_railway_ticket 33
#define menu_buzzer 74
#define menu_rosso_card 75
#define menu_toilet_key 36
#define menu_soap 76
#define menu_soap_imp 77
#define menu_soap_plas 78
#define menu_stone_key 79
#define menu_chalice 41
#define menu_tissue 42
#define menu_toilet_brush 80
#define menu_toilet_chain 44
#define menu_towel 45
#define menu_tripod 46
#define menu_lens 81
#define menu_towel_cut 48
#define menu_mirror 82
#define menu_tissue_charred 50
#define menu_cog_1 51
#define menu_cog_2 52
#define menu_handle 83
#define menu_coin 84
#define menu_biro 55
#define menu_pipe 56
#define menu_flashlight 57

#define IT_MCODE                1               // Call an mcode routine
#define IT_PUSHNUMBER           2               // push a number on the stack
#define IT_PUSHVARIABLE         3               // push a variable on the stack

#define IT_FIRSTOPERATOR        4              // Operators come after this and must stay in the same order for precedence table

#define IT_NOTEQUAL             4
#define IT_ISEQUAL              5
#define IT_PLUS                 6
#define IT_TIMES                7
#define IT_ANDAND               8
#define IT_OROR                 9
#define IT_LESSTHAN             10
#define IT_NOT                  11
#define IT_MINUS                12
#define IT_AND                  13
#define IT_OR                   14
#define IT_GTE			15		// >=
#define IT_LTE			16		// <=
#define IT_DEVIDE		17		// <=
#define IT_GT			18		// >

#define IT_SCRIPTEND            20
#define IT_POPVAR               21
#define IT_POPLONGOFFSET        22
#define IT_PUSHLONGOFFSET       23
#define IT_SKIPONFALSE          24
#define IT_SKIP                 25
#define IT_SWITCH               26
#define IT_SKIPONTRUE           27
#define IT_PRINTF               28
#define IT_RESTARTSCRIPT        30
#define IT_POPWORDOFFSET        31
#define IT_PUSHWORDOFFSET       32

enum ScriptVariableNames {
	RETURN_VALUE = 0,
	RETURN_VALUE_2,
	RETURN_VALUE_3,
	RETURN_VALUE_4,
	DEFAULT_ICON_TEXT,
	MENU_LOOKING,
	TOP_MENU_DISABLED,
	GEORGE_DOING_REST_ANIM,
	GEORGE_WALKING,
	ADVISOR_188_FLAG,
	MEGA_ON_GRID,
	REROUTE_GEORGE,
	WALK_FLAG,
	WALK_ATTEMPT,
	TARGET_X,
	TARGET_Y,
	DISTANCE_APART,
	ID_LOW_FLOOR,
	NEW_SCREEN,
	CUR_ID,
	MOUSE_STATUS,
	PALETTE,
	NEW_PALETTE,
	MOUSE_X,
	MOUSE_Y,
	SPECIAL_ITEM,
	CLICK_ID,
	MOUSE_BUTTON,
	BUTTON,
	BOTH_BUTTONS, // not used anymore
	SAFE_X,
	SAFE_Y,
	CHANGE_X,
	CHANGE_Y,
	CHANGE_PLACE,
	CHANGE_DIR,
	CHANGE_STANCE,
	SCROLL_FLAG,
	SCROLL_OFFSET_X,
	SCROLL_OFFSET_Y,
	MAX_SCROLL_OFFSET_X,
	MAX_SCROLL_OFFSET_Y,
	FEET_X,
	FEET_Y,
	SECOND_ITEM, //SECOND_ICON,
	SUBJECT_CHOSEN,
	IN_SUBJECT,
	DEBUG_FLAG_1,
	DEBUG_FLAG_2,
	DEBUG_FLAG_3,
	FIRST_WATCH,
	GEORGE_ALLOWED_REST_ANIMS,
	CURRENT_MUSIC,
	TESTLINENO,
	LASTLINENO,
	WANTPREVIOUSLINE,
	PLAYINGDEMO,
	TEMP_FLAG,
	PHOTOS_FLAG,
	PHONE_FLOOR_FLAG,
	PHONE_ROOM_FLAG,
	BENOIR_FLAG,
	GUARD_FLAG,
	MOUE_DOOR_FLAG,
	CANOPY_FLAG,
	GOT_NEWSPAPER_FLAG,
	DEMO_NICO_FLAG,
	NICO_TARGET,
	NICO_DIR,
	BEEN_TO_ALLEY,
	DUSTBIN_FLAG,
	DUSTBIN_2_FLAG,
	TRIED_MANHOLE_FLAG,
	MANHOLE_FLAG,
	DRAINPIPE_FLAG,
	OPENED_MANHOLE_2_BEFORE,
	SEARCHED_PLANTARD_FLAG,
	ENTERED_CAFE_ONCE,
	BOTTLE_3_FLAG,
	TOOLBOX_4_FLAG,
	CALL_ALB_FLAG,
	CALL_ALBERT_FLAG,
	GOT_NOSE_FLAG,
	GOT_MATERIAL_FLAG,
	GOT_TISSUE_FLAG,
	RAILING_7_FLAG,
	SEEN_FLOWERS_FLAG,
	SEEN_DRESS_SHOP_FLAG,
	DOOR_9_FLAG,
	PHONE_10_FLAG,
	MANUSCRIPT_ON_TABLE_10_FLAG,
	DOG_TURD_FLAG,
	PIERMONT_AT_PIANO_FLAG,
	GOT_KEY_FLAG,
	USED_HOTEL_KEY_ONCE,
	WINDOW_15_OPEN,
	CLIMBED_OUT_15_FLAG,
	WINDOW_16_FLAG,
	HOTEL_ASSASSIN_BEEN,
	WARDROBE_17_OPEN,
	SEARCHED_TROUSERS_17,
	ENTERED_17_FLAG,
	WINDOW_27_FLAG,
	CASE_1_LOCKED_FLAG,
	CASE_2_LOCKED_FLAG,
	CASE_3_LOCKED_FLAG,
	CASE_4_LOCKED_FLAG,
	SEEN_ARMOUR_28_FLAG,
	CLOSED_WINDOW_28_FLAG,
	WINDOW_28_FLAG,
	WINDOW_DRAUGHT_FLAG,
	SEEN_WINDOW_28_FLAG,
	FACING_WINDOW_FLAG,
	CLOSING_WINDOW_FLAG,
	SARCOPHAGUS_FLAG,
	ENTERED_MUSEUM_28_FLAG,
	SARCOPHAGUS_DOOR_29_OPEN,
	AMBULANCE_31_FLAG,
	CONSULTANT_HERE,
	SEEN_MR_SHINY_FLAG,
	SEEN_CUPBOARD_FLAG,
	PLUG_33_UNPLUGGED,
	SAM_RETURNING,
	PULLED_PLUG_33,
	PULSE_34_FLAG,
	DOOR_34_OPEN,
	MARQUET_AWAKE_FLAG,
	JUGGLER_FLAG,
	JUGGLE_FLAG,
	CROWD_FLAG,
	MANHOLE_36_FLAG,
	DOOR_37_FLAG,
	IN_BOAT_FLAG,
	GOT_HOOK_FLAG,
	HOOK_FLAG,
	STEPS_38_FLAG,
	TRIPOD_PUZZLE_FLAG,
	SOAP_43_FLAG,
	SEEN_WASHBASIN_43,
	HOSPITAL_FLAG,
	SEEN_PARIS_MAP,
	PHONE_SCREEN_FLAG,
	PHONE_PLACE_FLAG,
	SEAN_DEAD,
	SPAIN_VISIT,
	WET_BEER_TOWEL_TIMER,
	BEER_TOWEL_BEEN_WET,
	NICO_SCOT_SCREEN,
	NICO_AT_PANEL_72,
	NICO_POSITION_71,
	SEEN_DRAIN_19,
	SEEN_MENU_19,
	PUB_TRAP_DOOR,
	ASSASSIN_EIRE_DONE,
	BAR_TOWEL_TAKEN,
	GLASS_WASH_FLAG,
	PUB_DOOR_FLAG,
	PUB_FLAP_FLAG,
	DOYLE_DRINKING,
	RON_SNEEZING,
	FUSE_WIRE_TAKEN,
	FUSE_WIRE_ON_TABLE,
	GLASS_20_FLAG,
	MAGUIRE_PUB_DONE,
	PINT_LEVEL_FLAG,
	GEM_21_TAKEN,
	MAGUIRE_CEL_DONE,
	TORCH_21_TAKEN,
	BEEN_UP_HAYBAILS,
	LIFTING_KEYS_IN_HOLE_23,
	SEEN_STEPS_SEQUENCE,
	SEEN_GOAT_24,
	FLEECY_TANGLED,
	FLEECY_STUCK,
	FLEECY_BACKING_OFF,
	SEEN_LADDER_SEQUENCE,
	BUTT_COUNT_24,
	KEYSTONE_FLAG,
	PANEL_25_MOVED,
	SACK_25_FLAG,
	SAND_FLAG,
	SEEN_HOLES_25,
	REPLICA_IN_CAVITY,
	SEEN_RAT_26,
	ENTERED_CELLAR_BEFORE,
	CAT_ON_SHELF,
	CAT_RAN_OFF,
	CAT_TIMER,
	STATUETTE_FLAG,
	SEEN_TOP_SHELF_45,
	DUANE_TARGET,
	AYUB_OPENING_DOOR,
	GEORGE_TALKING_TO_PEARL,
	CARPET_DOOR_47_OPEN,
	TOILET_KEYS_ON_BAR,
	EXPLAINED_RETURNING_KEYS,
	DOOR_49_OPEN,
	TOILET_CHAIN_50_TAKEN,
	TOWEL_DISPENSER_50_OPEN,
	TOWEL_50_TAKEN,
	CUBICLE_DOOR_50_OPEN,
	DOOR_50_OPEN,
	MAX_ITERATION,
	ITERATION,
	STICK_54_FLAG,
	TOWEL_IN_CRACK_54,
	CAVE_54_OPEN,
	GUN_54_FLAG,
	KHAN_54_HERE,
	DOOR_55_OPEN,
	READ_INSCRIPTION_55,
	SEEN_STATUE_55,
	VISITED_COUNTESS_56_AGAIN,
	CHALICE_56_GIVEN,
	CHESS_PIECE_56_GIVEN,
	GARDENER_57_HERE,
	PRESSURE_GAUGE_57_FLAG,
	FOUND_WELL_57,
	DOOR_58_OPEN,
	COUNTESS_58_HERE,
	GARDENER_58_HERE,
	COUNTESS_59_HERE,
	BIBLE_59_FLAG,
	WINDOW_59_SHUT,
	CHALICE_59_TAKEN,
	SECRET_DOOR_59_OPEN,
	HOLDING_SNUFFER,
	TISSUE_ON_SNUFFER,
	TISSUE_59_CHARRED,
	TISSUE_59_BURNING,
	CANDLE_59_BURNT,
	LECTERN_CANDLES_59_LIT,
	TISSUE_FLAME_59_ON,
	GARDENER_60_POSITION,
	GARDENER_60_CHECKING_DOGS,
	DOGS_DISTURBED,
	MIRROR_60_TAKEN,
	SEEN_LEFT_ROCKFALL_61,
	LION_HEAD_FALLING,
	LION_FANG_FLAG,
	DOOR_61_FLAG,
	GEORGE_HOLDING_PIECE,
	CHESS_SQUARE_1_FLAG,
	CHESS_SQUARE_2_FLAG,
	CHESS_SQUARE_3_FLAG,
	CHESS_SQUARE_4_FLAG,
	CHESS_SQUARE_5_FLAG,
	DOOR_ONE_63_OPEN,
	DOOR_TWO_63_OPEN,
	DOOR_THREE_63_OPEN,
	GEORGE_ON_ROOF,
	SEEN_EKLUND_63,
	DOOR_65_OPEN,
	DOOR_67_OPEN,
	WINDOW_66_OPEN,
	SEQUENCE_69_FLAG,
	SC69_TIMER,
	LEFT_TREE_POINTER_71_FLAG,
	RIGHT_TREE_POINTER_71_FLAG,
	RUBBLE_72_FLAG,
	MACHINERY_HANDLE_FLAG,
	MACHINERY_COG_FLAG,
	DEMON_RB_FLAG,
	DEMON_LB_FLAG,
	DEMON_COGS_FLAG,
	DEMON_PIPE_FLAG,
	DEMON_NOSE_FLAG,
	DEMON_LEFT_COG_FLAG,
	DEMON_RIGHT_COG_FLAG,
	PANEL_72_FLAG,
	SEEN_CRYPT_73,
	SEEN_GUNPOWDER_73,
	GUIDO_73_HERE,
	NICO_POSITION_73,
	ALBERT_ANNOYED_FLAG,
	ALBERT_BRIEFCASE_FLAG,
	ALBERT_BUZZER_FLAG,
	ALBERT_CDT_FLAG,
	ALBERT_CHANTELLE_FLAG,
	ALBERT_CHAT_FLAG,
	ALBERT_CLOWN_FLAG,
	ALBERT_JACKET_FLAG,
	ALBERT_KEYS_FLAG,
	ALBERT_NOSE_FLAG,
	ALBERT_PLANTARD_FLAG,
	ALBERT_POLICE_FLAG,
	ALBERT_POS_FLAG,
	ALBERT_TALK_FLAG,
	ALBERT_TISSUE_FLAG,
	ALBERT_TEXT,
	ALBERT_INFO_FLAG,
	ARTO_BULL_FLAG,
	ARTO_BRUSH_FLAG,
	ARTO_IRRITATION_FLAG,
	ARTO_KLAUSNER_FLAG,
	ARTO_LOOM_FLAG,
	ARTO_OBJECT_FLAG,
	ARTO_PHRASE_FLAG,
	ARTO_TEXT,
	ASSASSIN_BOOK_FLAG,
	ASSASSIN_BULL_FLAG,
	ASSASSIN_CHURCH_FLAG,
	ASSASSIN_EIRE_TEXT,
	ASSASSIN_SWORD_FLAG,
	ASSASSIN_TEMPLAR_FLAG,
	ASSASSIN_TEXT,
	AYUB_BULL_FLAG,
	AYUB_KLAUSNER_FLAG,
	AYUB_LOOM_FLAG,
	AYUB_ULTAR_FLAG,
	AYUB_TEXT,
	BASHER_BEER_FLAG,
	BASHER_COMPLAIN_FLAG,
	BASHER_EKLUND_FLAG,
	BASHER_HELP_FLAG,
	BASHER_NICO_FLAG,
	BASHER_STOP_FLAG,
	BASHER_WEASEL_FLAG,
	BASHER_WINDOW_FLAG,
	BASHER_TEXT,
	BENOIR_BUZZER_FLAG,
	BENOIR_GAUGE_FLAG,
	BENOIR_MARQUET_FLAG,
	BENOIR_NURSE_FLAG,
	BENOIR_RENEE_FLAG,
	BENOIR_TEXT,
	CARPET_TEXT,
	CARPET_OBJECT_FLAG,
	CHANTELLE_BRIEFCASE_FLAG,
	CHANTELLE_CLOWN_FLAG,
	CHANTELLE_DOCTOR_FLAG,
	CHANTELLE_EYE_FLAG,
	CHANTELLE_FAINT_FLAG,
	CHANTELLE_NEWSPAPER_FLAG,
	CHANTELLE_PLANTARD_FLAG,
	CHANTELLE_TEXT,
	CHANTELLE_WAKE_COUNTER,
	CLERK_ASSASSIN_FLAG,
	CLERK_BUZZER_FLAG,
	CLERK_CLOWN_FLAG,
	CLERK_ENOUGH_FLAG,
	CLERK_HKEY_FLAG,
	CLERK_KEY_FLAG,
	CLERK_KEY_STOP_FLAG,
	CLERK_NOSE_FLAG,
	CLERK_PASS_FLAG,
	CLERK_PHOTO_FLAG,
	CLERK_PIERMONT_FLAG,
	CLERK_PLANTARD_FLAG,
	CLERK_POLITE_FLAG,
	CLERK_SAFE_FLAG,
	CLERK_TEMPLAR_FLAG,
	CLERK_TEXT,
	CLERK_TISSUE_FLAG,
	CLERK_WEASEL_FLAG,
	CONSULT_CHALICE_FLAG,
	CONSULT_GAUGE_FLAG,
	CONSULT_GEM_FLAG,
	CONSULT_LIFTKEY_FLAG,
	CONSULT_MARQUET_FLAG,
	CONSULT_NOSE_FLAG,
	CONSULT_PHOTO_FLAG,
	CONSULT_TEXT,
	CONSULT_TISSUE_FLAG,
	COSTUMIER_BALL_FLAG,
	COSTUMIER_BUZZER_FLAG,
	COSTUMIER_CLOWN_FLAG,
	COSTUMIER_PHOTO_FLAG,
	COSTUMIER_PLANTARD_FLAG,
	COSTUMIER_TISSUE_FLAG,
	COSTUMIER_TEXT,
	DOYLE_BEER_FLAG,
	DOYLE_BUZZER_FLAG,
	DOYLE_CASTLE_FLAG,
	DOYLE_DIG_FLAG,
	DOYLE_FLASHLIGHT_FLAG,
	DOYLE_GEM_FLAG,
	DOYLE_JEWEL_FLAG,
	DOYLE_JOB_FLAG,
	DOYLE_KEYS_FLAG,
	DOYLE_LEPRECHAUN_FLAG,
	DOYLE_NOSE_FLAG,
	DOYLE_PEAGRAM_FLAG,
	DOYLE_PHOTOGRAPH_FLAG,
	DOYLE_SEAN_FLAG,
	DOYLE_TEMPLAR_FLAG,
	DOYLE_TEXT,
	DOYLE_TISSUE_FLAG,
	DOYLE_TOWEL_FLAG,
	DUANE_ARTO_FLAG,
	DUANE_BULL_FLAG,
	DUANE_CLEVE_FLAG,
	DUANE_DUANE_FLAG,
	DUANE_PEARL_FLAG,
	DUANE_PHOTO_FLAG,
	DUANE_KEYS_FLAG,
	DUANE_MANUSCRIPT_FLAG,
	DUANE_NEJO_FLAG,
	DUANE_PHRASE_FLAG,
	DUANE_QUEEN_FLAG,
	DUANE_STATUETTE_FLAG,
	DUANE_TEMPLAR_FLAG,
	DUANE_TEXT,
	DUANE_ULTAR_FLAG,
	ERIC_MARQUET_FLAG,
	ERIC_NURSE_FLAG,
	ERIC_PHOTO_FLAG,
	EVA_CLOWN_FLAG,
	EVA_LENS_FLAG,
	EVA_MARQUET_FLAG,
	EVA_MOB_FLAG,
	EVA_NURSE_FLAG,
	EVA_TEXT,
	FARMER_BEER_FLAG,
	FARMER_BOOK_FLAG,
	FARMER_BUZZER_FLAG,
	FARMER_CAR_FLAG,
	FARMER_CASTLE_FLAG,
	FARMER_FLASHLIGHT_FLAG,
	FARMER_GEM_FLAG,
	FARMER_GHOST_FLAG,
	FARMER_LAST_STRAW,
	FARMER_LIFTKEYS_FLAG,
	FARMER_MOVED_FLAG,
	FARMER_NOSE_FLAG,
	FARMER_PASS_FLAG,
	FARMER_PEAGRAM_FLAG,
	FARMER_PHOTO_FLAG,
	FARMER_SEAN_FLAG,
	FARMER_TEMPLAR_FLAG,
	FARMER_TEXT,
	FARMER_TISSUE_FLAG,
	FARMER_WIRE_FLAG,
	FLEECY_TEXT,
	FLOWER_FLOWER_FLAG,
	FLOWER_FORTUNE_FLAG,
	FLOWER_GAUGE_FLAG,
	FLOWER_GEM_FLAG,
	FLOWER_LIFTKEYS_FLAG,
	FLOWER_NICO_FLAG,
	FLOWER_PASS_FLAG,
	FLOWER_PHOTO_FLAG,
	FLOWER_TEXT,
	GARD_ATTEMPT,
	GARD_BY_WELL,
	GARDENER_COUNTESS_FLAG,
	GARDENER_CHALICE_FLAG,
	GARDENER_FLOPPO_FLAG,
	GARDENER_GOODBYE_FLAG,
	GARDENER_HOSE_FLAG,
	GARDENER_IRRITATION,
	GARDENER_SPEECH_FLAG,
	GARDENER_TEMPLAR_FLAG,
	GARDENER_TEXT,
	GATEKEEPER_TALK_FLAG,
	GATEKEEPER_CDT_FLAG,
	GMASTER_TALK_FLAG,
	GMASTER_CDT_FLAG,
	GENDARME_CARD_FLAG,
	GENDARME_CLOWN_FLAG,
	GENDARME_MOUE_FLAG,
	GENDARME_NOSE_FLAG,
	GEND_PAPER_FLAG,
	GENDARME_PHOTO_FLAG,
	GENDARME_ROSSO_FLAG,
	GENDARME_TEXT,
	GENDARME_TISSUE_FLAG,
	GENDARME_WEASEL_FLAG,
	GOINFRE_ALARM_FLAG,
	GOINFRE_EXHIBIT_FLAG,
	GOINFRE_GEM_FLAG,
	GOINFRE_KEYS_FLAG,
	GOINFRE_LOBINEAU_FLAG,
	GOINFRE_MS_FLAG,
	GOINFRE_SARCOPHAGUS_FLAG,
	GOINFRE_SCOLD_FLAG,
	GOINFRE_TEMPLAR_FLAG,
	GOINFRE_TEXT,
	GOINFRE_TISSUE_FLAG,
	GOINFRE_TRIPOD_FLAG,
	GOINFRE_WINDOW_FLAG,
	GORILLA_CLOWN_FLAG,
	GORILLA_KHAN_FLAG,
	GORILLA_PASS_FLAG,
	GORILLA_PLANTARD_FLAG,
	GORILLA_SEARCH_FLAG,
	GORILLA_TEXT,
	GORILLA_TISSUE_FLAG,
	GORILLA_WEASEL_FLAG,
	HOSCOP_ALERT_FLAG,
	HOSCOP_MARQUET_FLAG,
	HOSCOP_MOB_FLAG,
	HOSCOP_TEXT,
	JUGGLER_JUGGLER_FLAG,
	JUGGLER_TEMPLAR_FLAG,
	JUGGLER_GEM_FLAG,
	JUGGLER_TEXT,
	KHAN_SUBJECT_FLAG,
	KHAN_PREAMBLE_FLAG,
	LATVIAN_CLOWN_FLAG,
	LATVIAN_EYE_FLAG,
	LATVIAN_LIFTKEYS_FLAG,
	LATVIAN_MATCHBOOK_FLAG,
	LATVIAN_MS_FLAG,
	LATVIAN_NOSE_FLAG,
	LATVIAN_PHOTO_FLAG,
	LATVIAN_PLANTARD_FLAG,
	LATVIAN_TEXT,
	LEARY_BEER_FLAG,
	LEARY_BUZZER_FLAG,
	LEARY_CASTLE_FLAG,
	LEARY_CLOWN_FLAG,
	LEARY_FISH_FLAG,
	LEARY_FLAP_FLAG,
	LEARY_FLAPALERT_FLAG,
	LEARY_KEYS_FLAG,
	LEARY_NOSE_FLAG,
	LEARY_PASS_FLAG,
	LEARY_PEAGRAM_FLAG,
	LEARY_PHONE_FLAG,
	LEARY_PHOTO_FLAG,
	LEARY_PLASTER_FLAG,
	LEARY_PLUG_FLAG,
	LEARY_SEAN_FLAG,
	LEARY_SNARE_FLAG,
	LEARY_TEMPLAR_FLAG,
	LEARY_TEXT,
	LEARY_TISSUE_FLAG,
	LEARY_TOWEL_FLAG,
	LEARY_WASHER_FLAG,
	LEARY_WILD_FLAG,
	LEARY_WIRE_FLAG,
	LOBINEAU_ARTEFACT_FLAG,
	LOBINEAU_BALL_FLAG,
	LOBINEAU_BEL_FLAG,
	LOBINEAU_GEM_FLAG,
	LOBINEAU_HASH_FLAG,
	LOBINEAU_KEYS_FLAG,
	LOBINEAU_MANUSCRIPT_FLAG,
	LOBINEAU_MATCHBOOK_FLAG,
	LOBINEAU_MONTFAUCON_FLAG,
	LOBINEAU_NICO_FLAG,
	LOBINEAU_PANTS_FLAG,
	LOBINEAU_PEAGRAM_FLAG,
	LOBINEAU_STATUE_FLAG,
	LOBINEAU_SYRIA_FLAG,
	LOBINEAU_TEMPLAR_FLAG,
	LOBINEAU_TEXT,
	LOBINEAU_TRIPOD_FLAG,
	MAGUIRE_CAR_FLAG,
	MAGUIRE_CASTLE_FLAG,
	MAGUIRE_CDT_FLAG,
	MAGUIRE_CLOWN_FLAG,
	MAGUIRE_COP_FLAG,
	MAGUIRE_DIG_FLAG,
	MAGUIRE_GEM_FLAG,
	MAGUIRE_GHOST_FLAG,
	MAGUIRE_JEWEL_FLAG,
	MAGUIRE_KEYS_FLAG,
	MAGUIRE_LEPRECHAUN_FLAG,
	MAGUIRE_NOSE_FLAG,
	MAGUIRE_PEAGRAM_FLAG,
	MAGUIRE_SEAN_FLAG,
	MAGUIRE_SHOCK_FLAG,
	MAGUIRE_TALK_FLAG,
	MAGUIRE_TEXT,
	MAGUIRE_WIRE_FLAG,
	MANAGER_TEXT,
	MANAGER_BRUSH_FLAG,
	MANAGER_SPEECH_FLAG,
	MOUE_BALL_FLAG,
	MOUE_BRIEFCASE_FLAG,
	MOUE_CARD_FLAG,
	MOUE_CDT_FLAG,
	MOUE_CLOWN_FLAG,
	MOUE_EYE_FLAG,
	MOUE_FETCH_FLAG,
	MOUE_HASH_FLAG,
	MOUE_KEY_FLAG,
	MOUE_MARQUET_FLAG,
	MOUE_MATCHBOOK_FLAG,
	MOUE_MATERIAL_FLAG,
	MOUE_MOB_FLAG,
	MOUE_NEWSPAPER_FLAG,
	MOUE_NICO_FLAG,
	MOUE_NOSE_FLAG,
	MOUE_PHOTO_FLAG,
	MOUE_PLANTARD_FLAG,
	MOUE_ROSSO_FLAG,
	MOUE_STOP_FLAG,
	MOUE_TALK_FLAG,
	MOUE_TEXT,
	MOUE_TISSUE_FLAG,
	NEJO_ARTO_FLAG,
	NEJO_AYUB_FLAG,
	NEJO_BALL_FLAG,
	NEJO_BALL_TALK,
	NEJO_BULL_FLAG,
	NEJO_CAT_FLAG,
	NEJO_CHALICE_FLAG,
	NEJO_DOLLAR_FLAG,
	NEJO_GOODBYE_FLAG,
	NEJO_HENDERSONS_FLAG,
	NEJO_LOOM_FLAG,
	NEJO_NEJO_FLAG,
	NEJO_PHRASE_FLAG,
	NEJO_PLASTER_FLAG,
	NEJO_PRESSURE_GAUGE_FLAG,
	NEJO_STALL_FLAG,
	NEJO_STATUE_FLAG,
	NEJO_TEMPLAR_FLAG,
	NEJO_TEXT,
	NEJO_ULTAR_FLAG,
	NICO_ALBERT_FLAG,
	NICO_ASSASSIN_FLAG,
	NICO_BALL_FLAG,
	NICO_BRIEFCASE_FLAG,
	NICO_BULL_FLAG,
	NICO_BUZZER_FLAG,
	NICO_CHALICE_FLAG,
	NICO_CDT_FLAG,
	NICO_CLOWN_FLAG,
	NICO_EKLUND_FLAG,
	NICO_GAUGE_FLAG,
	NICO_GEM_FLAG,
	NICO_GOODBYE_FLAG,
	NICO_GUIDO_FLAG,
	NICO_HASH_FLAG,
	NICO_IRELAND_FLAG,
	NICO_KNIGHT_FLAG,
	NICO_LIFTKEYS_FLAG,
	NICO_LENS_FLAG,
	NICO_LOBINEAU_FLAG,
	NICO_MANUSCRIPT_FLAG,
	NICO_MARQUET_FLAG,
	NICO_MATCHBOOK_FLAG,
	NICO_MATERIAL_FLAG,
	NICO_NEWSPAPER_FLAG,
	NICO_NICO_FLAG,
	NICO_NOSE_FLAG,
	NICO_PASS_FLAG,
	NICO_PEAGRAM_FLAG,
	NICO_PLANTARD_FLAG,
	NICO_PLASTER_FLAG,
	NICO_PHOTO_FLAG,
	NICO_PHONE_TEXT,
	NICO_POS_FLAG,
	NICO_QUEEN_FLAG,
	NICO_RINGING_BACK_FLAG,
	NICO_ROSSO_FLAG,
	NICO_SEWER_FLAG,
	NICO_SPAIN_FLAG,
	NICO_SYRIA_FLAG,
	NICO_TALK_FLAG,
	NICO_TEMPLAR_FLAG,
	NICO_TEXT,
	NICO_TISSUE_FLAG,
	NICO_TRAIN_FLAG,
	NICO_TRIPOD_FLAG,
	NICO_WEAVER_FLAG,
	NIC_BAG_TALK_FLAG,
	NIC_BAG_CDT_FLAG,
	NICO_LEAVING_CAFE_SCREEN,
	NURSE_BENOIR_FLAG,
	NURSE_CLOWN_FLAG,
	NURSE_GAUGE_FLAG,
	NURSE_MARQUET_FLAG,
	NURSE_INTERRUPTION_FLAG,
	NURSE_TEXT,
	OBRIEN_BUZZER_FLAG,
	OBRIEN_CASTLE_FLAG,
	OBRIEN_FLASHLIGHT_FLAG,
	OBRIEN_GEM_FLAG,
	OBRIEN_JEWEL_FLAG,
	OBRIEN_JOB_FLAG,
	OBRIEN_KEYS_FLAG,
	OBRIEN_LEARY_FLAG,
	OBRIEN_MAGUIRE_FLAG,
	OBRIEN_NOSE_FLAG,
	OBRIEN_PEAGRAM_FLAG,
	OBRIEN_SEAN_FLAG,
	OBRIEN_TEMPLAR_FLAG,
	OBRIEN_TEXT,
	OBRIEN_TISSUE_FLAG,
	OBRIEN_TOWEL_FLAG,
	OLD_NOSE_FLAG,
	OLD_PHOTO_FLAG,
	OLD_LIFT_FLAG,
	OLD_BUZZER_FLAG,
	PAINTER_DIG_FLAG,
	PAINTER_DISTRACTION_FLAG,
	PAINTER_PAINTER_FLAG,
	PAINTER_TEMPLAR_FLAG,
	PAINTER_CONTROL_FLAG,
	PAINTER_TEXT,
	PEARL_AKRON_FLAG,
	PEARL_ARTO_FLAG,
	PEARL_BULL_FLAG,
	PEARL_DUANE_FLAG,
	PEARL_NEJO_FLAG,
	PEARL_PEARL_FLAG,
	PEARL_PHRASE_FLAG,
	PEARL_POEMS_FLAG,
	PEARL_STATUE_FLAG,
	PEARL_TEMPLAR_FLAG,
	PEARL_TEXT,
	PEARL_ULTAR_FLAG,
	PEARL_TALK_FLAG,
	PEARL_CDT_FLAG,
	PEARL_STALL_FLAG,
	PEARL_WEAVER_FLAG,
	PIERMONT_ASSASSIN_FLAG,
	PIERMONT_BUZZER_FLAG,
	PIERMONT_CLOWN_FLAG,
	PIERMONT_GEM_FLAG,
	PIERMONT_HKEY_FLAG,
	PIERMONT_KEY_FLAG,
	PIERMONT_KEY_ALERT_FLAG,
	PIERMONT_MS_FLAG,
	PIERMONT_NOSE_FLAG,
	PIERMONT_PASS_FLAG,
	PIERMONT_PHOTO_FLAG,
	PIERMONT_PIERMONT_FLAG,
	PIERMONT_TEMPLAR_FLAG,
	PIERMONT_TEXT,
	PIERMONT_TISSUE_FLAG,
	PIERMONT_WEASEL_FLAG,
	PRIEST_TEXT,
	PRIEST_CHALICE_FLAG,
	PRIEST_CHALICE2_FLAG,
	PRIEST_TEMPLAR_FLAG,
	PRIEST_PRIEST_FLAG,
	PRIEST_WINDO1_FLAG,
	PRIEST_WINDO2_FLAG,
	PRIEST_WINDO3_FLAG,
	RENEE_MARQUET_FLAG,
	RENEE_PHOTO_FLAG,
	RENEE_RENEE_FLAG,
	RENEE_TEXT,
	RON_ALERT_FLAG,
	RON_BEER_FLAG,
	RON_CASTLE_FLAG,
	RON_DIG_FLAG,
	RON_FLASHLIGHT_FLAG,
	RON_GHOST_FLAG,
	RON_NOSE_FLAG,
	RON_PASS_FLAG,
	RON_PEAGRAM_FLAG,
	RON_PHOTO_FLAG,
	RON_POLICE_FLAG,
	RON_SEAN_FLAG,
	RON_SNARE_FLAG,
	RON_STOP_FLAG,
	RON_TEXT,
	RON_UPSET_FLAG,
	ROSSO_CDT_FLAG,
	ROSSO_CLOWN_FLAG,
	ROSSO_DOCTOR_FLAG,
	ROSSO_FORTUNE_FLAG,
	ROSSO_GEM_FLAG,
	ROSSO_MARQUET_FLAG,
	ROSSO_MATCHBOOK_FLAG,
	ROSSO_MOUE_FLAG,
	ROSSO_OPINION_FLAG,
	ROSSO_PASS_FLAG,
	ROSSO_PEAGRAM_FLAG,
	ROSSO_PHOTO_FLAG,
	ROSSO_PLANTARD_FLAG,
	ROSSO_ROSSO_FLAG,
	ROSSO_TALK_FLAG,
	ROSSO_TEMPLAR_FLAG,
	ROSSO_TEXT,
	ROSSO_THUGS_FLAG,
	ROZZER_36_FLAG,
	ROZZER_JUGGLER_FLAG,
	ROZZER_MANHOLE_FLAG,
	ROZZER_PLASTER_FLAG,
	ROZZER_ROZZER_FLAG,
	ROZZER_TEMPLAR_FLAG,
	ROZZER_TEXT,
	SAM_BREAKDOWN_FLAG,
	SAM_BUZZER_FLAG,
	SAM_CUPBOARD_FLAG,
	SAM_GEM_FLAG,
	SAM_MARQUET_FLAG,
	SAM_MATCHBOOK_FLAG,
	SAM_MOB_FLAG,
	SAM_NOSE_FLAG,
	SAM_NURSE_FLAG,
	SAM_PHOTO_FLAG,
	SAM_PLASTER_FLAG,
	SAM_SHINY_FLAG,
	SAM_SOCKET_FLAG,
	SAM_STOP_FLAG,
	SAM_TEXT,
	SEAN_ASSASSIN_FLAG,
	SEAN_BEER_FLAG,
	SEAN_CASTLE_FLAG,
	SEAN_DIG_FLAG,
	SEAN_GEM_FLAG,
	SEAN_LKEYS_FLAG,
	SEAN_NOSE_FLAG,
	SEAN_OPINION,
	SEAN_PACKAGE_FLAG,
	SEAN_PEAGRAM_FLAG,
	SEAN_SELF_FLAG,
	SEAN_SNAP_FLAG,
	SEAN_TEXT,
	STATUE_GUARD_CONTROL_FLAG,
	STATUE_GUARD_FLAG,
	STATUE_GUARD_GUARD_FLAG,
	STATUE_GUARD_KEY,
	GUARD_GLOVE_FLAG,
	STATUE_GUARD_TEMPLAR_FLAG,
	STATUE_GUARD_THERMO_FLAG,
	STATUE_GUARD_TEXT,
	STATUE_GUARD_TALK_FLAG,
	STATUE_GUARD_CDT_FLAG,
	TCLERK_PIERMONT_FLAG,
	TNIC_ENQUIRY_FLAG,
	TODRYK_CLOWN_FLAG,
	TODRYK_EYE_FLAG,
	TODRYK_GEORGE_FLAG,
	TODRYK_OPINION_FLAG,
	TODRYK_PHOTO_FLAG,
	TODRYK_PLANTARD_FLAG,
	TODRYK_ROSSO_FLAG,
	TODRYK_TEXT,
	ULTAR_ARTO_FLAG,
	ULTAR_BALL_FLAG,
	ULTAR_BULL_FLAG,
	ULTAR_BUZZER_FLAG,
	ULTAR_CHALICE_FLAG,
	ULTAR_CLUB_FLAG,
	ULTAR_DOLLARS_FLAG,
	ULTAR_GOODBYE_FLAG,
	ULTAR_HENDERSONS_FLAG,
	ULTAR_KLAUSNER_FLAG,
	ULTAR_LAB_PASS_FLAG,
	ULTAR_LIFTING_KEYS_FLAG,
	ULTAR_LOOM_FLAG,
	ULTAR_NEJO_FLAG,
	ULTAR_PHOTOGRAPH_FLAG,
	ULTAR_PHRASE_FLAG,
	ULTAR_PRESSURE_GAUGE_FLAG,
	ULTAR_RED_NOSE_FLAG,
	ULTAR_SIGN_FLAG,
	ULTAR_STATUETTE_FLAG,
	ULTAR_STATUETTE_PAINT_FLAG,
	ULTAR_TISSUE_FLAG,
	ULTAR_TEMPLAR_FLAG,
	ULTAR_TAXI_FLAG,
	ULTAR_TOILET_BRUSH_FLAG,
	ULTAR_TOILET_CHAIN_FLAG,
	ULTAR_TOILET_KEY_FLAG,
	ULTAR_TOWEL_FLAG,
	ULTAR_PLASTER_FLAG,
	ULTAR_TEXT,
	COUNTESS_56A_SUBJECT_FLAG,
	COUNTESS_56A_GOODBYE_FLAG,
	COUNTESS_56B_GOODBYE_FLAG,
	COUNTESS_TALK_FLAG,
	COUNTESS_CDT_FLAG,
	VAS_BALL_FLAG,
	VAS_COUNTESS_FLAG,
	VAS_GOODBYE_FLAG,
	VAS_KEY_FLAG,
	VAS_PHOTO_FLAG,
	VAS_TALK,
	VAS_TEXT,
	VAS_TEXT_TOGGLE,
	VAS_TEMPLAR_FLAG,
	VAS_CURSE_FLAG,
	VAS_PCHALICE_FLAG,
	GEORGE59A,
	VAIL_TEXT,
	VAIL_TALK_FLAG,
	VAIL_CDT_FLAG,
	WEASEL_CLOWN_FLAG,
	WEASEL_KHAN_FLAG,
	WEASEL_GUIDO_FLAG,
	WEASEL_PLANTARD_FLAG,
	WEASEL_ROSSO_FLAG,
	WEASEL_STOP_FLAG,
	WEASEL_TEXT,
	WORKMAN_CLOWN_FLAG,
	WORKMAN_COP_FLAG,
	WORKMAN_PHONE_ALERT_FLAG,
	WORKMAN_PLANTARD_FLAG,
	WORKMAN_ROSSO_CARD,
	WORKMAN_STOP_FLAG,
	WORKMAN_TOOL_FLAG,
	WORKMAN_TOOLBOX_FLAG,
	WORKMAN_TEXT,
	GEORGE_TALK_FLAG,
	GEORGE_CDT_FLAG,
	CHOOSER_COUNT_FLAG,
	HURRY_FLAG,
	IRELAND_FLAG,
	IRELAND_MAP_FLAG,
	KNOWS_PEAGRAM_FLAG,
	KNOWS_PHILIP_FLAG,
	MANUSCRIPT_FLAG,
	OBJECT_HELD,
	OBJECT_ICON,
	OBJECT_TALK,
	PARIS_FLAG,
	RESPONSERECEIVED,
	SCENE_FLAG,
	SCREEN,
	SCORE_FLAG,
	SCOTLAND_MAP_FLAG,
	SPAIN_MAP_FLAG,
	SYRIA_FLAG,
	TALK_FLAG,
	WEIRD_ZONE,
	TARGET_MEGA,
	CHURCH_ARRIVAL_FLAG,
	SHH_ALERT_FLAG,
	AEROPORT_ADDRESS_FLAG,
	CHANTELLE_BRANDY_FLAG,
	CHURCH_FLAG,
	CHOOSE_GAUGE_FLAG,
	CLERK_AT_DESK_FLAG,
	CONSULTANT_STOP_FLAG,
	COSTUMES_ADDRESS_FLAG,
	COSTUMES_PHONE_FLAG,
	FOUND_WARD_FLAG,
	GEORGE_POS_FLAG,
	GOT_BENOIR_FLAG,
	HOLE_FLAG,
	HOSPITAL_ADDRESS_FLAG,
	HOSPITAL_VISIT_FLAG,
	HOS_POS_FLAG,
	HOTEL_ADDRESS_FLAG,
	IRELAND_ALERT_FLAG,
	KEY_ALERT_FLAG,
	KEYRING_FLAG,
	KEY_TALK,
	KNOWS_MOERLIN_FLAG,
	LENS_FLAG,
	MACDEVITTS_PHONE_FLAG,
	MANUSCRIPT_ALERT_FLAG,
	MANUSCRIPT_VIEW_FLAG,
	MEETING_FLAG,
	MESSAGE_FLAG,
	MONTFACN_ADDRESS_FLAG,
	MONTFAUCON_CONTROL_FLAG,
	MUSEUM_ADDRESS_FLAG,
	MUSEUM_CLOSING_FLAG,
	MUSEUM_PHONE_FLAG,
	NERVAL_ADDRESS_FLAG,
	NICO_ADDRESS_FLAG,
	NICO_APT_FLAG,
	NICO_DOOR_FLAG,
	NICO_GONE_HOME_FLAG,
	NICO_PHONE_FLAG,
	NICO_VISIT_FLAG,
	NURSE_TELEPHONE_FLAG,
	PAINT_TALK,
	PAINTPOT_FLAG,
	PARIS_STATUE_FLAG,
	PHONE_CHECK,
	PHONE_REQUEST,
	POLICE_ADDRESS_FLAG,
	POLICE_PHONE_FLAG,
	POLISHER_PLUG_FLAG,
	POS_FLAG,
	RADIO_ALERT_FLAG,
	READ_NEWSPAPER,
	READ_NOSE_FLAG,
	SARCOPHAGUS_ALERT_FLAG,
	SC28_COIN_FLAG,
	SC28_POTTERY_FLAG,
	SC48_SCROLL_FLAG,
	SEEN_BRIEFCASE_FLAG,
	SEEN_DOOR22_FLAG,
	SEEN_KEY_FLAG,
	SEEN_MANHOLE_FLAG,
	SEEN_PLANTARD_FLAG,
	SEEN_REGISTER_FLAG,
	SEEN_SEWERS_FLAG,
	SEEN_TRIPOD_FLAG,
	SEWER_EXIT_FLAG,
	SKIP_TALK,
	SOAP_FLAG,
	ERIC_TEXT,
	TAILOR_PHONE_FLAG,
	THERMO_FLAG,
	TOILET_TALK,
	TOMB_FLAG,
	TORCH_ALERT_FLAG,
	TOTEM_ALERT_FLAG,
	TRIPOD_FLAG,
	TRIPOD_ALERT_FLAG,
	TRIPOD_STOLEN_FLAG,
	WARD_STOP_FLAG,
	WHITE_COAT_FLAG,
	WINDOW_ALERT_FLAG,
	WORKMAN_GONE_FLAG,
	CLIMBING_CART_FLAG,
	FIDDLER_TEXT,
	PEAGRAM_GONE_FLAG,
	PINT_FLAG,
	PUB_ELEC_FLAG,
	PUB_INTERRUPTION_FLAG,
	PUB_TAP_FLAG,
	SEEN_GOAT_FLAG,
	SYRIA_BOOK_FLAG,
	SEEN_BRUSH_FLAG,
	SEEN_STATUE_FLAG,
	SYRIA_DEAD_FLAG,
	SYRIA_NICHE_FLAG,
	ARMOUR_HIDE_FLAG,
	CANDLE59_FLAG,
	CANDLE_BURNT,
	CHALICE_FLAG,
	CHESSET_FLAG,
	CHESSBOARD_FLAG,
	DOOR_REVEALED,
	DOWSE_FLAG,
	GEORGE_POSITION,
	GEORGE_SAFE,
	GEORGE_WELL_FLAG,
	HAZEL_FLAG,
	INTRO_FLAG,
	LION_FANG,
	LOGS_56_FLAG,
	MARY_FLAG,
	MIRROR_HINT,
	ROCKFALL_1,
	ROCKFALL_2,
	SECOND_CURSE_FLAG,
	SPAIN_CODA,
	TOMBS59_FLAG,
	ASSASSIN_KILLED_FLAG,
	AXE_ALERT_FLAG,
	DOOR_SC69_ALERT_FLAG,
	DOOR_SC65_FLAG,
	EKLUND_KILLED,
	FINALE_OPTION_FLAG,
	NICO_GONE_FLAG,
	NICO_TIED_FLAG,
	PIPE_ALERT_FLAG,
	SEEN_GUIDO_63,
	END_SCENE,
	MASTER_39_TALK_FLAG,
	MASTER_39_CDT_FLAG,
	COLONEL_TALK_FLAG,
	COLONEL_CDT_FLAG,
	EXEC_TALK_FLAG,
	EXEC_CDT_FLAG,
	CIVIL_TALK_FLAG,
	CIVIL_CDT_FLAG,
	LATVIAN_39_TALK_FLAG,
	LATVIAN_39_CDT_FLAG,
	EKLUND_39_TALK_FLAG,
	EKLUND_39_CDT_FLAG,
	CAFE_BOMBED,
	BLIND_ALLEY,
	CAFE_INTERIOR,
	ROAD_WORKS,
	COURT_YARD,
	SEWER_ONE,
	SEWER_TWO,
	CAFE_REPAIRED,
	APT_STREET,
	APT_NICO,
	COSTUME_SHOP,
	HOTEL_STREET,
	HOTEL_DESK,
	HOTEL_CORRIDOR,
	HOTEL_EMPTY,
	HOTEL_LEDGE,
	HOTEL_ASSASSIN,
	GENDARMERIE,
	IRELAND_STREET,
	MACDEVITTS,
	PUB_CELLAR,
	CASTLE_GATE,
	CASTLE_HAY_TOP,
	CASTLE_YARD,
	CASTLE_DIG,
	CELLAR_DARK,
	MUSEUM_STREET,
	MUSEUM_ONE,
	MUSEUM_TWO,
	MUSEUM_HIDING,
	HOSPITAL_STREET,
	HOSPITAL_DESK,
	HOSPITAL_CORRIDOR,
	HOSPITAL_WARD,
	HOSPITAL_JACQUES,
	MONTFAUCON,
	CATACOMB_SEWER,
	CATACOMB_ROOM,
	CATACOMB_MEETING,
	EXCAVATION_EXT,
	EXCAVATION_LOBBY,
	EXCAVATION_DIG,
	EXCAVATION_TOILET,
	EXCAVATION_SECRET,
	TEMPLAR_CHURCH,
	SYRIA_STALL,
	SYRIA_CARPET,
	SYRIA_CLUB,
	SYRIA_TOILET,
	BULL_CLIFF,
	BULL_INTERIOR,
	MAUSOLEUM_EXT,
	SPAIN_DRIVE,
	SPAIN_GARDEN,
	MAUSOLEUM_INT,
	SPAIN_RECEPTION,
	SPAIN_WELL,
	SPAIN_SECRET,
	TRAIN_ONE,
	TRAIN_TWO,
	COMPT_ONE,
	COMPT_TWO,
	COMPT_THREE,
	COMPT_FOUR,
	TRAIN_GUARD,
	CHURCHYARD,
	CHURCH_TOWER,
	CRYPT,
	SECRET_CRYPT,
	POCKET_1,
	POCKET_2,
	POCKET_3,
	POCKET_4,
	POCKET_5,
	POCKET_6,
	POCKET_7,
	POCKET_8,
	POCKET_9,
	POCKET_10,
	POCKET_11,
	POCKET_12,
	POCKET_13,
	POCKET_14,
	POCKET_15,
	POCKET_16,
	POCKET_17,
	POCKET_18,
	POCKET_19,
	POCKET_20,
	POCKET_21,
	POCKET_22,
	POCKET_23,
	POCKET_24,
	POCKET_25,
	POCKET_26,
	POCKET_27,
	POCKET_28,
	POCKET_29,
	POCKET_30,
	POCKET_31,
	POCKET_32,
	POCKET_33,
	POCKET_34,
	POCKET_35,
	POCKET_36,
	POCKET_37,
	POCKET_38,
	POCKET_39,
	POCKET_40,
	POCKET_41,
	POCKET_42,
	POCKET_43,
	POCKET_44,
	POCKET_45,
	POCKET_46,
	POCKET_47,
	POCKET_48,
	POCKET_49,
	POCKET_50,
	POCKET_51,
	POCKET_52
};

#define SAND_25 1638407
#define HOLDING_REPLICA_25 1638408
#define GMASTER_79 5177345
#define SCR_std_off (0*0x10000 + 6)
#define SCR_exit0 (0*0x10000 + 7)
#define SCR_exit1 (0*0x10000 + 8)
#define SCR_exit2 (0*0x10000 + 9)
#define SCR_exit3 (0*0x10000 + 10)
#define SCR_exit4 (0*0x10000 + 11)
#define SCR_exit5 (0*0x10000 + 12)
#define SCR_exit6 (0*0x10000 + 13)
#define SCR_exit7 (0*0x10000 + 14)
#define SCR_exit8 (0*0x10000 + 15)
#define SCR_exit9 (0*0x10000 + 16)
#define LEFT_SCROLL_POINTER 8388610
#define RIGHT_SCROLL_POINTER 8388611
#define FLOOR_63 4128768
#define ROOF_63 4128779
#define GUARD_ROOF_63 4128781
#define LEFT_TREE_POINTER_71 4653058
#define RIGHT_TREE_POINTER_71 4653059
#define SCR_menu_look (0*0x10000 + 24)
#define SCR_icon_combine_script (0*0x10000 + 25)

} // End of namespace Sword1

#endif //SWORDDEFS_H
