/*
	This file is automatically generated by make_func.
	do not make any manual changes to this file.
*/

{
{"B2G",F_B2G,0,0,1,1,TYPE_STRING,T_STRING,T_ANY,T_ANY,T_ANY,20,DEFAULT_NONE},
{"G2B",F_G2B,0,0,1,1,TYPE_STRING,T_STRING,T_ANY,T_ANY,T_ANY,20,DEFAULT_NONE},
{"_call_other",F__CALL_OTHER,0,0,2,-1,TYPE_UNKNOWN,T_OBJECT|T_STRING|T_ARRAY,T_STRING|T_ARRAY,T_ANY,T_ANY,0,DEFAULT_NONE},
{"_evaluate",F__EVALUATE,0,0,1,-1,TYPE_ANY,T_ANY,T_ANY,T_ANY,T_ANY,8,DEFAULT_NONE},
{"_new",F__NEW,0,0,1,-1,TYPE_OBJECT,T_STRING,T_ANY,T_ANY,T_ANY,20,DEFAULT_NONE},
{"_this_object",F__THIS_OBJECT,0,0,0,0,TYPE_OBJECT,T_ANY,T_ANY,T_ANY,T_ANY,0,DEFAULT_NONE},
{"_to_float",F__TO_FLOAT,0,0,1,1,TYPE_REAL,T_STRING|T_REAL|T_NUMBER,T_ANY,T_ANY,T_ANY,16,DEFAULT_NONE},
{"_to_int",F__TO_INT,0,0,1,1,TYPE_NUMBER,T_STRING|T_REAL|T_NUMBER|T_BUFFER,T_ANY,T_ANY,T_ANY,11,DEFAULT_NONE},
{"abs",F_ABS,0,0,1,1,TYPE_ANY,T_NUMBER|T_REAL,T_ANY,T_ANY,T_ANY,76,DEFAULT_NONE},
{"acos",F_ACOS,0,0,1,1,TYPE_REAL,T_REAL,T_ANY,T_ANY,T_ANY,77,DEFAULT_NONE},
{"act_mxp",F_ACT_MXP,0,0,0,0,TYPE_NOVALUE,T_ANY,T_ANY,T_ANY,T_ANY,0,DEFAULT_NONE},
{"add_action",F_ADD_ACTION,0,0,2,3,TYPE_NOVALUE,T_STRING|T_FUNCTION,T_STRING|T_ARRAY,T_NUMBER,T_ANY,87,DEFAULT_NONE},
{"addn",F_ADDN,0,0,2,3,TYPE_ANY,T_STRING,T_NUMBER,T_OBJECT,T_ANY,277,DEFAULT_NONE},
{"addn_temp",F_ADDN_TEMP,0,0,2,3,TYPE_ANY,T_STRING,T_NUMBER,T_OBJECT,T_ANY,277,DEFAULT_NONE},
{"all_inventory",F_ALL_INVENTORY,0,0,1,1,TYPE_MOD_ARRAY|TYPE_OBJECT,T_OBJECT,T_ANY,T_ANY,T_ANY,25,DEFAULT_THIS_OBJECT},
{"all_previous_objects",F_PREVIOUS_OBJECT | F_ALIAS_FLAG,0,0,1,1,TYPE_MOD_ARRAY|TYPE_OBJECT,T_NUMBER,T_ANY,T_ANY,T_ANY,18,-1},
{"allocate",F_ALLOCATE,0,0,1,2,TYPE_MOD_ARRAY|TYPE_ANY,T_NUMBER,T_ANY,T_ANY,T_ANY,166,DEFAULT_NONE},
{"allocate_buffer",F_ALLOCATE_BUFFER,0,0,1,1,TYPE_BUFFER,T_NUMBER,T_ANY,T_ANY,T_ANY,18,DEFAULT_NONE},
{"allocate_mapping",F_ALLOCATE_MAPPING,0,0,1,2,TYPE_MAPPING,T_NUMBER|T_ARRAY,T_ANY,T_ANY,T_ANY,136,DEFAULT_NONE},
{"angle",F_ANGLE,0,0,2,2,TYPE_REAL,T_ARRAY|T_ARRAY,T_ARRAY|T_ARRAY,T_ANY,T_ANY,289,DEFAULT_NONE},
{"ansi",F_ANSI,0,0,1,1,TYPE_STRING,T_STRING,T_ANY,T_ANY,T_ANY,20,DEFAULT_NONE},
{"ansi_part",F_ANSI_PART,0,0,1,1,TYPE_STRING,T_STRING,T_ANY,T_ANY,T_ANY,20,DEFAULT_NONE},
{"arrayp",F_POINTERP | F_ALIAS_FLAG,0,0,1,1,TYPE_NUMBER,T_ANY,T_ANY,T_ANY,T_ANY,8,DEFAULT_NONE},
{"asin",F_ASIN,0,0,1,1,TYPE_REAL,T_REAL,T_ANY,T_ANY,T_ANY,77,DEFAULT_NONE},
{"assemble_class",F_ASSEMBLE_CLASS,0,0,1,1,TYPE_ANY,T_ARRAY,T_ANY,T_ANY,T_ANY,5,DEFAULT_NONE},
{"async_db_exec",F_ASYNC_DB_EXEC,0,0,3,3,TYPE_NOVALUE,T_NUMBER,T_STRING,T_FUNCTION,T_ANY,386,DEFAULT_NONE},
{"async_getdir",F_ASYNC_GETDIR,0,0,2,2,TYPE_NOVALUE,T_STRING,T_FUNCTION,T_ANY,T_ANY,388,DEFAULT_NONE},
{"async_read",F_ASYNC_READ,0,0,2,2,TYPE_NOVALUE,T_STRING,T_FUNCTION,T_ANY,T_ANY,388,DEFAULT_NONE},
{"async_write",F_ASYNC_WRITE,0,0,4,4,TYPE_NOVALUE,T_STRING,T_STRING,T_NUMBER,T_FUNCTION,392,DEFAULT_NONE},
{"atan",F_ATAN,0,0,1,1,TYPE_REAL,T_REAL,T_ANY,T_ANY,T_ANY,77,DEFAULT_NONE},
{"base_name",F_BASE_NAME,0,0,1,1,TYPE_STRING,T_STRING|T_OBJECT,T_ANY,T_ANY,T_ANY,338,DEFAULT_THIS_OBJECT},
{"bg5cc",F_BG5CC,0,0,1,1,TYPE_STRING,T_STRING,T_ANY,T_ANY,T_ANY,20,DEFAULT_NONE},
{"bind",F_BIND,0,0,2,2,TYPE_FUNCTION,T_FUNCTION,T_OBJECT,T_ANY,T_ANY,23,DEFAULT_NONE},
{"bufferp",F_BUFFERP,0,0,1,1,TYPE_NUMBER,T_ANY,T_ANY,T_ANY,T_ANY,8,DEFAULT_NONE},
{"buftostr",F_BUFTOSTR,0,0,1,1,TYPE_STRING,T_BUFFER,T_ANY,T_ANY,T_ANY,14,DEFAULT_NONE},
{"cache_stats",F_CACHE_STATS,0,0,0,0,TYPE_STRING,T_ANY,T_ANY,T_ANY,T_ANY,0,DEFAULT_NONE},
{"call_other",F__CALL_OTHER | F_ALIAS_FLAG,0,0,2,-1,TYPE_ANY,T_OBJECT|T_STRING|T_ARRAY,T_STRING|T_ARRAY,T_ANY,T_ANY,0,DEFAULT_NONE},
{"call_out",F_CALL_OUT,0,0,2,-1,TYPE_NUMBER,T_STRING|T_FUNCTION,T_NUMBER,T_ANY,T_ANY,38,DEFAULT_NONE},
{"call_out_info",F_CALL_OUT_INFO,0,0,0,0,TYPE_MOD_ARRAY|TYPE_ANY,T_ANY,T_ANY,T_ANY,T_ANY,0,DEFAULT_NONE},
{"call_stack",F_CALL_STACK,0,0,1,1,TYPE_MOD_ARRAY|TYPE_ANY,T_NUMBER,T_ANY,T_ANY,T_ANY,18,0},
{"capitalize",F_CAPITALIZE,0,0,1,1,TYPE_STRING,T_STRING,T_ANY,T_ANY,T_ANY,20,DEFAULT_NONE},
{"ceil",F_CEIL,0,0,1,1,TYPE_REAL,T_REAL,T_ANY,T_ANY,T_ANY,77,DEFAULT_NONE},
{"children",F_CHILDREN,0,0,1,1,TYPE_MOD_ARRAY|TYPE_OBJECT,T_STRING,T_ANY,T_ANY,T_ANY,20,DEFAULT_NONE},
{"classes",F_CLASSES,0,0,2,2,TYPE_MOD_ARRAY|TYPE_ANY,T_OBJECT,T_NUMBER,T_ANY,T_ANY,204,0},
{"classp",F_CLASSP,0,0,1,1,TYPE_NUMBER,T_ANY,T_ANY,T_ANY,T_ANY,8,DEFAULT_NONE},
{"clear_bit",F_CLEAR_BIT,0,0,2,2,TYPE_STRING,T_STRING,T_NUMBER,T_ANY,T_ANY,102,DEFAULT_NONE},
{"clone_object",F__NEW | F_ALIAS_FLAG,0,0,1,-1,TYPE_OBJECT,T_STRING,T_ANY,T_ANY,T_ANY,20,DEFAULT_NONE},
{"clonep",F_CLONEP,0,0,1,1,TYPE_NUMBER,T_ANY,T_ANY,T_ANY,T_ANY,8,DEFAULT_THIS_OBJECT},
{"command",F_COMMAND,0,0,1,1,TYPE_NUMBER,T_STRING,T_ANY,T_ANY,T_ANY,20,DEFAULT_NONE},
{"commands",F_COMMANDS,0,0,0,0,TYPE_MOD_ARRAY|TYPE_ANY,T_ANY,T_ANY,T_ANY,T_ANY,0,DEFAULT_NONE},
{"compress",F_COMPRESS,0,0,1,1,TYPE_BUFFER,T_STRING|T_BUFFER,T_ANY,T_ANY,T_ANY,118,DEFAULT_NONE},
{"compress_file",F_COMPRESS_FILE,0,0,1,2,TYPE_NUMBER,T_STRING,T_STRING,T_ANY,T_ANY,27,DEFAULT_NONE},
{"compressedp",F_COMPRESSEDP,0,0,1,1,TYPE_NUMBER,T_OBJECT,T_ANY,T_ANY,T_ANY,25,DEFAULT_NONE},
{"copy",F_COPY,0,0,1,1,TYPE_ANY,T_ANY,T_ANY,T_ANY,T_ANY,8,DEFAULT_NONE},
{"cos",F_COS,0,0,1,1,TYPE_REAL,T_REAL,T_ANY,T_ANY,T_ANY,77,DEFAULT_NONE},
{"count",F_COUNT,0,0,3,3,TYPE_ANY,T_ANY,T_STRING,T_ANY,T_ANY,257,DEFAULT_NONE},
{"cp",F_CP,0,0,2,2,TYPE_NUMBER,T_STRING,T_STRING,T_ANY,T_ANY,27,DEFAULT_NONE},
{"crc32",F_CRC32,0,0,1,1,TYPE_NUMBER,T_STRING|T_BUFFER,T_ANY,T_ANY,T_ANY,118,DEFAULT_NONE},
{"crypt",F_CRYPT,0,0,2,2,TYPE_STRING,T_STRING,T_STRING|T_NUMBER,T_ANY,T_ANY,111,DEFAULT_NONE},
{"ctime",F_CTIME,0,0,0,1,TYPE_STRING,T_NUMBER,T_ANY,T_ANY,T_ANY,18,DEFAULT_NONE},
{"cwrap",F_CWRAP,0,0,1,3,TYPE_STRING,T_STRING,T_NUMBER,T_NUMBER,T_ANY,192,DEFAULT_NONE},
{"db_affected",F_DB_AFFECTED,0,0,1,1,TYPE_NUMBER,T_NUMBER,T_ANY,T_ANY,T_ANY,18,DEFAULT_NONE},
{"db_close",F_DB_CLOSE,0,0,1,1,TYPE_NUMBER,T_NUMBER,T_ANY,T_ANY,T_ANY,18,DEFAULT_NONE},
{"db_commit",F_DB_COMMIT,0,0,1,1,TYPE_NUMBER,T_NUMBER,T_ANY,T_ANY,T_ANY,18,DEFAULT_NONE},
{"db_connect",F_DB_CONNECT,0,0,2,4,TYPE_NUMBER,T_STRING,T_STRING,T_STRING,T_NUMBER,263,DEFAULT_NONE},
{"db_exec",F_DB_EXEC,0,0,2,2,TYPE_ANY,T_NUMBER,T_STRING,T_ANY,T_ANY,18,DEFAULT_NONE},
{"db_fetch",F_DB_FETCH,0,0,2,2,TYPE_MOD_ARRAY|TYPE_ANY,T_NUMBER,T_NUMBER,T_ANY,T_ANY,49,DEFAULT_NONE},
{"db_rollback",F_DB_ROLLBACK,0,0,1,1,TYPE_NUMBER,T_NUMBER,T_ANY,T_ANY,T_ANY,18,DEFAULT_NONE},
{"db_status",F_DB_STATUS,0,0,0,1,TYPE_STRING,T_ANY,T_ANY,T_ANY,T_ANY,3,DEFAULT_NONE},
{"debug_info",F_DEBUG_INFO,0,0,2,2,TYPE_ANY,T_NUMBER,T_OBJECT,T_ANY,T_ANY,196,DEFAULT_NONE},
{"debug_message",F_DEBUG_MESSAGE,0,0,1,1,TYPE_NOVALUE,T_STRING,T_ANY,T_ANY,T_ANY,20,DEFAULT_NONE},
{"deep_inherit_list",F_DEEP_INHERIT_LIST,0,0,1,1,TYPE_MOD_ARRAY|TYPE_STRING,T_OBJECT,T_ANY,T_ANY,T_ANY,25,DEFAULT_THIS_OBJECT},
{"deep_inventory",F_DEEP_INVENTORY,0,0,1,2,TYPE_MOD_ARRAY|TYPE_OBJECT,T_OBJECT|T_ARRAY|T_FUNCTION,T_FUNCTION,T_ANY,T_ANY,57,DEFAULT_THIS_OBJECT},
{"defer",F_DEFER,0,0,1,1,TYPE_NOVALUE,T_FUNCTION,T_ANY,T_ANY,T_ANY,23,DEFAULT_NONE},
{"delete",F_DELETE,0,0,1,2,TYPE_NOVALUE,T_STRING,T_OBJECT,T_ANY,T_ANY,83,DEFAULT_NONE},
{"delete_temp",F_DELETE_TEMP,0,0,1,2,TYPE_NOVALUE,T_STRING,T_OBJECT,T_ANY,T_ANY,83,DEFAULT_NONE},
{"destruct",F_DESTRUCT,0,0,1,1,TYPE_NOVALUE,T_OBJECT,T_ANY,T_ANY,T_ANY,25,DEFAULT_THIS_OBJECT},
{"disable_commands",F_DISABLE_COMMANDS,0,0,0,0,TYPE_NOVALUE,T_ANY,T_ANY,T_ANY,T_ANY,0,DEFAULT_NONE},
{"disable_wizard",F_DISABLE_WIZARD,0,0,0,0,TYPE_NOVALUE,T_ANY,T_ANY,T_ANY,T_ANY,0,DEFAULT_NONE},
{"disassemble_class",F_DISASSEMBLE_CLASS,0,0,1,1,TYPE_MOD_ARRAY|TYPE_ANY,T_ANY,T_ANY,T_ANY,T_ANY,8,DEFAULT_NONE},
{"distance",F_DISTANCE,0,0,2,2,TYPE_REAL,T_ARRAY|T_ARRAY,T_ARRAY|T_ARRAY,T_ANY,T_ANY,289,DEFAULT_NONE},
{"dotprod",F_DOTPROD,0,0,2,2,TYPE_REAL,T_ARRAY|T_ARRAY,T_ARRAY|T_ARRAY,T_ANY,T_ANY,292,DEFAULT_NONE},
{"dump_file_descriptors",F_DUMP_FILE_DESCRIPTORS,0,0,0,0,TYPE_STRING,T_ANY,T_ANY,T_ANY,T_ANY,0,DEFAULT_NONE},
{"dump_prog",F_DUMP_PROG,0,0,1,-1,TYPE_NOVALUE,T_OBJECT,T_ANY,T_ANY,T_ANY,298,DEFAULT_NONE},
{"dumpallobj",F_DUMPALLOBJ,0,0,0,1,TYPE_NOVALUE,T_STRING,T_ANY,T_ANY,T_ANY,20,DEFAULT_NONE},
{"ed",F_ED,0,0,0,5,TYPE_NOVALUE,T_STRING,T_STRING|T_NUMBER,T_STRING|T_NUMBER,T_NUMBER,221,DEFAULT_NONE},
{"element_of",F_ELEMENT_OF,0,0,1,1,TYPE_ANY,T_ARRAY,T_ANY,T_ANY,T_ANY,5,DEFAULT_NONE},
{"enable_commands",F_ENABLE_COMMANDS,0,0,0,0,TYPE_NOVALUE,T_ANY,T_ANY,T_ANY,T_ANY,0,DEFAULT_NONE},
{"enable_wizard",F_ENABLE_WIZARD,0,0,0,0,TYPE_NOVALUE,T_ANY,T_ANY,T_ANY,T_ANY,0,DEFAULT_NONE},
{"environment",F_ENVIRONMENT,0,0,0,1,TYPE_OBJECT,T_OBJECT,T_ANY,T_ANY,T_ANY,25,DEFAULT_NONE},
{"error",F_ERROR,0,0,1,1,TYPE_NOVALUE,T_STRING,T_ANY,T_ANY,T_ANY,20,DEFAULT_NONE},
{"eval_cost",F_SET_EVAL_LIMIT | F_ALIAS_FLAG,0,0,1,1,TYPE_NUMBER,T_NUMBER,T_ANY,T_ANY,T_ANY,18,-1},
{"evaluate",F__EVALUATE | F_ALIAS_FLAG,0,0,1,-1,TYPE_ANY,T_ANY,T_ANY,T_ANY,T_ANY,8,DEFAULT_NONE},
{"event",F_EVENT,0,0,2,-1,TYPE_NOVALUE,T_OBJECT|T_ARRAY,T_STRING,T_ANY,T_ANY,332,DEFAULT_NONE},
{"exec",F_EXEC,0,0,2,2,TYPE_NUMBER,T_OBJECT,T_OBJECT,T_ANY,T_ANY,198,DEFAULT_NONE},
{"exp",F_EXP,0,0,1,1,TYPE_REAL,T_REAL,T_ANY,T_ANY,T_ANY,77,DEFAULT_NONE},
{"explode",F_EXPLODE,0,0,2,2,TYPE_MOD_ARRAY|TYPE_STRING,T_STRING,T_STRING,T_ANY,T_ANY,27,DEFAULT_NONE},
{"export_uid",F_EXPORT_UID,0,0,1,1,TYPE_NUMBER,T_OBJECT,T_ANY,T_ANY,T_ANY,25,DEFAULT_NONE},
{"external_start",F_EXTERNAL_START,0,0,4,5,TYPE_NUMBER,T_NUMBER,T_STRING|T_ARRAY,T_STRING|T_FUNCTION,T_STRING|T_FUNCTION,306,DEFAULT_NONE},
{"fetch_class_member",F_FETCH_CLASS_MEMBER,0,0,2,2,TYPE_ANY,T_ANY,T_NUMBER,T_ANY,T_ANY,164,DEFAULT_NONE},
{"fetch_variable",F_FETCH_VARIABLE,0,0,1,2,TYPE_ANY,T_STRING,T_OBJECT,T_ANY,T_ANY,83,DEFAULT_NONE},
{"file_length",F_FILE_LENGTH,0,0,1,1,TYPE_NUMBER,T_STRING,T_ANY,T_ANY,T_ANY,20,DEFAULT_NONE},
{"file_name",F_FILE_NAME,0,0,1,1,TYPE_STRING,T_OBJECT,T_ANY,T_ANY,T_ANY,25,DEFAULT_THIS_OBJECT},
{"file_size",F_FILE_SIZE,0,0,1,1,TYPE_NUMBER,T_STRING,T_ANY,T_ANY,T_ANY,20,DEFAULT_NONE},
{"filter",F_FILTER,0,0,2,-1,TYPE_ANY,T_STRING|T_ARRAY|T_MAPPING,T_STRING|T_FUNCTION,T_ANY,T_ANY,233,DEFAULT_NONE},
{"filter_array",F_FILTER | F_ALIAS_FLAG,0,0,2,-1,TYPE_ANY,T_ARRAY,T_STRING|T_FUNCTION,T_ANY,T_ANY,215,DEFAULT_NONE},
{"filter_mapping",F_FILTER | F_ALIAS_FLAG,0,0,2,-1,TYPE_MAPPING,T_MAPPING,T_STRING|T_FUNCTION,T_ANY,T_ANY,235,DEFAULT_NONE},
{"find_call_out",F_FIND_CALL_OUT,0,0,1,1,TYPE_NUMBER,T_NUMBER|T_STRING,T_ANY,T_ANY,T_ANY,133,DEFAULT_NONE},
{"find_living",F_FIND_LIVING,0,0,1,1,TYPE_OBJECT,T_STRING,T_ANY,T_ANY,T_ANY,20,DEFAULT_NONE},
{"find_object",F_FIND_OBJECT,0,0,2,2,TYPE_OBJECT,T_STRING,T_NUMBER,T_ANY,T_ANY,102,0},
{"find_player",F_FIND_PLAYER,0,0,1,1,TYPE_OBJECT,T_STRING,T_ANY,T_ANY,T_ANY,20,DEFAULT_NONE},
{"first_inventory",F_FIRST_INVENTORY,0,0,1,1,TYPE_OBJECT,T_OBJECT|T_STRING,T_ANY,T_ANY,T_ANY,63,DEFAULT_THIS_OBJECT},
{"floatp",F_FLOATP,0,0,1,1,TYPE_NUMBER,T_ANY,T_ANY,T_ANY,T_ANY,8,DEFAULT_NONE},
{"floor",F_FLOOR,0,0,1,1,TYPE_REAL,T_REAL,T_ANY,T_ANY,T_ANY,77,DEFAULT_NONE},
{"flush_messages",F_FLUSH_MESSAGES,0,0,0,1,TYPE_NOVALUE,T_OBJECT,T_ANY,T_ANY,T_ANY,25,DEFAULT_NONE},
{"function_exists",F_FUNCTION_EXISTS,0,0,1,3,TYPE_STRING,T_STRING,T_OBJECT,T_NUMBER,T_ANY,202,DEFAULT_NONE},
{"function_owner",F_FUNCTION_OWNER,0,0,1,1,TYPE_OBJECT,T_FUNCTION,T_ANY,T_ANY,T_ANY,23,DEFAULT_NONE},
{"function_profile",F_FUNCTION_PROFILE,0,0,1,1,TYPE_MOD_ARRAY|TYPE_MAPPING,T_OBJECT,T_ANY,T_ANY,T_ANY,25,DEFAULT_THIS_OBJECT},
{"functionp",F_FUNCTIONP,0,0,1,1,TYPE_NUMBER,T_ANY,T_ANY,T_ANY,T_ANY,8,DEFAULT_NONE},
{"functions",F_FUNCTIONS,0,0,2,2,TYPE_MOD_ARRAY|TYPE_ANY,T_OBJECT,T_NUMBER,T_ANY,T_ANY,204,0},
{"get_char",F_GET_CHAR,0,0,1,-1,TYPE_NUMBER,T_STRING|T_FUNCTION,T_ANY,T_ANY,T_ANY,53,DEFAULT_NONE},
{"get_config",F_GET_CONFIG,0,0,1,1,TYPE_ANY,T_NUMBER,T_ANY,T_ANY,T_ANY,18,DEFAULT_NONE},
{"get_dir",F_GET_DIR,0,0,2,2,TYPE_MOD_ARRAY|TYPE_ANY,T_STRING,T_NUMBER,T_ANY,T_ANY,102,0},
{"get_garbage",F_GET_GARBAGE,0,0,0,0,TYPE_MOD_ARRAY|TYPE_OBJECT,T_ANY,T_ANY,T_ANY,T_ANY,0,DEFAULT_NONE},
{"geteuid",F_GETEUID,0,0,1,1,TYPE_STRING,T_FUNCTION|T_OBJECT,T_ANY,T_ANY,T_ANY,254,DEFAULT_THIS_OBJECT},
{"getuid",F_GETUID,0,0,1,1,TYPE_STRING,T_OBJECT,T_ANY,T_ANY,T_ANY,25,DEFAULT_THIS_OBJECT},
{"hash",F_HASH,0,0,2,2,TYPE_STRING,T_STRING,T_STRING,T_ANY,T_ANY,27,DEFAULT_NONE},
{"heart_beats",F_HEART_BEATS,0,0,0,0,TYPE_MOD_ARRAY|TYPE_OBJECT,T_ANY,T_ANY,T_ANY,T_ANY,0,DEFAULT_NONE},
{"implode",F_IMPLODE,0,0,2,3,TYPE_ANY,T_ARRAY,T_STRING|T_FUNCTION,T_ANY,T_ANY,31,DEFAULT_NONE},
{"in_edit",F_IN_EDIT,0,0,1,1,TYPE_STRING,T_OBJECT,T_ANY,T_ANY,T_ANY,25,DEFAULT_THIS_OBJECT},
{"in_input",F_IN_INPUT,0,0,1,1,TYPE_NUMBER,T_OBJECT,T_ANY,T_ANY,T_ANY,25,DEFAULT_THIS_OBJECT},
{"inherit_list",F_SHALLOW_INHERIT_LIST | F_ALIAS_FLAG,0,0,1,1,TYPE_MOD_ARRAY|TYPE_STRING,T_OBJECT,T_ANY,T_ANY,T_ANY,25,DEFAULT_THIS_OBJECT},
{"inherits",F_INHERITS,0,0,2,2,TYPE_NUMBER,T_STRING,T_OBJECT,T_ANY,T_ANY,83,DEFAULT_THIS_OBJECT},
{"input_to",F_INPUT_TO,0,0,1,-1,TYPE_NUMBER,T_STRING|T_FUNCTION,T_ANY,T_ANY,T_ANY,53,DEFAULT_NONE},
{"interactive",F_INTERACTIVE,0,0,1,1,TYPE_NUMBER,T_OBJECT,T_ANY,T_ANY,T_ANY,25,DEFAULT_THIS_OBJECT},
{"intp",F_INTP,0,0,1,1,TYPE_NUMBER,T_ANY,T_ANY,T_ANY,T_ANY,8,DEFAULT_NONE},
{"is_daylight_savings_time",F_IS_DAYLIGHT_SAVINGS_TIME,0,0,2,2,TYPE_NUMBER,T_STRING,T_NUMBER,T_ANY,T_ANY,102,DEFAULT_NONE},
{"keys",F_KEYS,0,0,1,1,TYPE_MOD_ARRAY|TYPE_ANY,T_MAPPING,T_ANY,T_ANY,T_ANY,141,DEFAULT_NONE},
{"kill_repeat_ansi",F_KILL_REPEAT_ANSI,0,0,1,1,TYPE_STRING,T_STRING,T_ANY,T_ANY,T_ANY,20,DEFAULT_NONE},
{"link",F_LINK,0,0,2,2,TYPE_NUMBER,T_STRING,T_STRING,T_ANY,T_ANY,27,DEFAULT_NONE},
{"living",F_LIVING,0,0,1,1,TYPE_NUMBER,T_OBJECT,T_ANY,T_ANY,T_ANY,25,DEFAULT_THIS_OBJECT},
{"livings",F_LIVINGS,0,0,0,0,TYPE_MOD_ARRAY|TYPE_OBJECT,T_ANY,T_ANY,T_ANY,T_ANY,0,DEFAULT_NONE},
{"load_object",F_FIND_OBJECT | F_ALIAS_FLAG,0,0,2,2,TYPE_OBJECT,T_STRING,T_NUMBER,T_ANY,T_ANY,102,1},
{"localtime",F_LOCALTIME,0,0,1,1,TYPE_MOD_ARRAY|TYPE_ANY,T_NUMBER,T_ANY,T_ANY,T_ANY,18,DEFAULT_NONE},
{"log",F_LOG,0,0,1,1,TYPE_REAL,T_REAL,T_ANY,T_ANY,T_ANY,77,DEFAULT_NONE},
{"log10",F_LOG10,0,0,1,1,TYPE_REAL,T_REAL|T_NUMBER,T_ANY,T_ANY,T_ANY,17,DEFAULT_NONE},
{"log2",F_LOG2,0,0,1,1,TYPE_REAL,T_REAL|T_NUMBER,T_ANY,T_ANY,T_ANY,17,DEFAULT_NONE},
{"lower_case",F_LOWER_CASE,0,0,1,1,TYPE_STRING,T_STRING,T_ANY,T_ANY,T_ANY,20,DEFAULT_NONE},
{"luan",F_LUAN,0,0,1,1,TYPE_NOVALUE,T_STRING,T_ANY,T_ANY,T_ANY,20,DEFAULT_NONE},
{"malloc_status",F_MALLOC_STATUS,0,0,0,0,TYPE_STRING,T_ANY,T_ANY,T_ANY,T_ANY,0,DEFAULT_NONE},
{"map",F_MAP,0,0,2,-1,TYPE_ANY,T_STRING|T_MAPPING|T_ARRAY,T_STRING|T_FUNCTION,T_ANY,T_ANY,241,DEFAULT_NONE},
{"map_array",F_MAP | F_ALIAS_FLAG,0,0,2,-1,TYPE_MOD_ARRAY|TYPE_ANY,T_ARRAY,T_STRING|T_FUNCTION,T_ANY,T_ANY,215,DEFAULT_NONE},
{"map_delete",F_MAP_DELETE,0,0,2,2,TYPE_NOVALUE,T_MAPPING,T_ANY,T_ANY,T_ANY,143,DEFAULT_NONE},
{"map_mapping",F_MAP | F_ALIAS_FLAG,0,0,2,-1,TYPE_MAPPING,T_MAPPING,T_STRING|T_FUNCTION,T_ANY,T_ANY,235,DEFAULT_NONE},
{"mapp",F_MAPP,0,0,1,1,TYPE_NUMBER,T_ANY,T_ANY,T_ANY,T_ANY,8,DEFAULT_NONE},
{"master",F_MASTER,0,0,0,0,TYPE_OBJECT,T_ANY,T_ANY,T_ANY,T_ANY,0,DEFAULT_NONE},
{"match_path",F_MATCH_PATH,0,0,2,2,TYPE_ANY,T_MAPPING,T_STRING,T_ANY,T_ANY,147,DEFAULT_NONE},
{"max",F_MAX,0,0,2,2,TYPE_ANY,T_ARRAY,T_NUMBER,T_ANY,T_ANY,47,0},
{"max_eval_cost",F_SET_EVAL_LIMIT | F_ALIAS_FLAG,0,0,1,1,TYPE_NUMBER,T_NUMBER,T_ANY,T_ANY,T_ANY,18,1},
{"mb_delete",F_MB_DELETE,0,0,1,-1,TYPE_NOVALUE,T_STRING,T_ANY,T_ANY,T_ANY,20,DEFAULT_NONE},
{"mb_query",F_MB_QUERY,0,0,1,-1,TYPE_ANY,T_STRING,T_ANY,T_ANY,T_ANY,20,DEFAULT_NONE},
{"mb_set",F_MB_SET,0,0,2,-1,TYPE_ANY,T_STRING,T_ANY,T_ANY,T_ANY,301,DEFAULT_NONE},
{"member_array",F_MEMBER_ARRAY,0,0,2,4,TYPE_NUMBER,T_ANY,T_STRING|T_ARRAY,T_NUMBER,T_NUMBER,44,DEFAULT_NONE},
{"memory_info",F_MEMORY_INFO,0,0,0,1,TYPE_NUMBER,T_OBJECT,T_ANY,T_ANY,T_ANY,25,DEFAULT_NONE},
{"memory_summary",F_MEMORY_SUMMARY,0,0,0,0,TYPE_MAPPING,T_ANY,T_ANY,T_ANY,T_ANY,0,DEFAULT_NONE},
{"message",F_MESSAGE,0,0,3,4,TYPE_NOVALUE,T_ANY,T_ANY,T_STRING|T_ARRAY|T_OBJECT|T_ARRAY,T_OBJECT|T_ARRAY,121,DEFAULT_NONE},
{"milli_clock",F_MILLI_CLOCK,0,0,0,0,TYPE_NUMBER,T_ANY,T_ANY,T_ANY,T_ANY,0,DEFAULT_NONE},
{"min",F_MIN,0,0,2,2,TYPE_ANY,T_ARRAY,T_NUMBER,T_ANY,T_ANY,47,0},
{"mkdir",F_MKDIR,0,0,1,1,TYPE_NUMBER,T_STRING,T_ANY,T_ANY,T_ANY,20,DEFAULT_NONE},
{"move_object",F_MOVE_OBJECT,0,0,1,1,TYPE_NOVALUE,T_OBJECT|T_STRING,T_ANY,T_ANY,T_ANY,63,DEFAULT_NONE},
{"mud_status",F_MUD_STATUS,0,0,1,1,TYPE_STRING,T_NUMBER,T_ANY,T_ANY,T_ANY,18,0},
{"named_livings",F_NAMED_LIVINGS,0,0,0,0,TYPE_MOD_ARRAY|TYPE_OBJECT,T_ANY,T_ANY,T_ANY,T_ANY,0,DEFAULT_NONE},
{"network_stats",F_NETWORK_STATS,0,0,0,0,TYPE_MAPPING,T_ANY,T_ANY,T_ANY,T_ANY,0,DEFAULT_NONE},
{"next_bit",F_NEXT_BIT,0,0,2,2,TYPE_NUMBER,T_STRING,T_NUMBER,T_ANY,T_ANY,102,DEFAULT_NONE},
{"next_inventory",F_NEXT_INVENTORY,0,0,1,1,TYPE_OBJECT,T_OBJECT,T_ANY,T_ANY,T_ANY,25,DEFAULT_THIS_OBJECT},
{"noansi_strlen",F_NOANSI_STRLEN,0,0,1,1,TYPE_NUMBER,T_STRING,T_ANY,T_ANY,T_ANY,20,DEFAULT_NONE},
{"norm",F_NORM,0,0,1,1,TYPE_REAL,T_ARRAY|T_ARRAY,T_ANY,T_ANY,T_ANY,289,DEFAULT_NONE},
{"notify_fail",F_NOTIFY_FAIL,0,0,1,1,TYPE_NOVALUE,T_STRING|T_FUNCTION,T_ANY,T_ANY,T_ANY,33,DEFAULT_NONE},
{"nullp",F_UNDEFINEDP | F_ALIAS_FLAG,0,0,1,1,TYPE_NUMBER,T_ANY,T_ANY,T_ANY,T_ANY,8,DEFAULT_NONE},
{"num_classes",F_NUM_CLASSES,0,0,1,1,TYPE_NUMBER,T_OBJECT,T_ANY,T_ANY,T_ANY,25,DEFAULT_NONE},
{"objectp",F_OBJECTP,0,0,1,1,TYPE_NUMBER,T_ANY,T_ANY,T_ANY,T_ANY,8,DEFAULT_NONE},
{"objects",F_OBJECTS,0,0,0,1,TYPE_MOD_ARRAY|TYPE_OBJECT,T_STRING|T_FUNCTION,T_ANY,T_ANY,T_ANY,33,DEFAULT_NONE},
{"oldcrypt",F_OLDCRYPT,0,0,2,2,TYPE_STRING,T_STRING,T_STRING|T_NUMBER,T_ANY,T_ANY,111,DEFAULT_NONE},
{"origin",F_ORIGIN,0,0,0,0,TYPE_STRING,T_ANY,T_ANY,T_ANY,T_ANY,0,DEFAULT_NONE},
{"pluralize",F_PLURALIZE,0,0,1,1,TYPE_STRING,T_STRING,T_ANY,T_ANY,T_ANY,20,DEFAULT_NONE},
{"pointerp",F_POINTERP,0,0,1,1,TYPE_NUMBER,T_ANY,T_ANY,T_ANY,T_ANY,8,DEFAULT_NONE},
{"pow",F_POW,0,0,2,2,TYPE_REAL,T_REAL|T_NUMBER,T_REAL|T_NUMBER,T_ANY,T_ANY,283,DEFAULT_NONE},
{"present",F_PRESENT,0,0,1,2,TYPE_OBJECT,T_OBJECT|T_STRING,T_OBJECT,T_ANY,T_ANY,82,DEFAULT_NONE},
{"previous_object",F_PREVIOUS_OBJECT,0,0,1,1,TYPE_ANY,T_NUMBER,T_ANY,T_ANY,T_ANY,18,0},
{"printf",F_PRINTF,0,0,1,-1,TYPE_NOVALUE,T_STRING,T_ANY,T_ANY,T_ANY,20,DEFAULT_NONE},
{"program_info",F_PROGRAM_INFO,0,0,0,1,TYPE_MAPPING,T_OBJECT,T_ANY,T_ANY,T_ANY,25,DEFAULT_NONE},
{"query",F_QUERY,0,0,1,2,TYPE_ANY,T_STRING,T_OBJECT,T_ANY,T_ANY,83,DEFAULT_NONE},
{"query_charmode",F_QUERY_CHARMODE,0,0,1,1,TYPE_NUMBER,T_OBJECT,T_ANY,T_ANY,T_ANY,25,DEFAULT_NONE},
{"query_heart_beat",F_QUERY_HEART_BEAT,0,0,1,1,TYPE_NUMBER,T_OBJECT,T_ANY,T_ANY,T_ANY,25,DEFAULT_THIS_OBJECT},
{"query_heartbeat_interval",F_QUERY_HEARTBEAT_INTERVAL,0,0,0,0,TYPE_NUMBER,T_ANY,T_ANY,T_ANY,T_ANY,0,DEFAULT_NONE},
{"query_host_name",F_QUERY_HOST_NAME,0,0,0,0,TYPE_STRING,T_ANY,T_ANY,T_ANY,T_ANY,0,DEFAULT_NONE},
{"query_idle",F_QUERY_IDLE,0,0,1,1,TYPE_NUMBER,T_OBJECT,T_ANY,T_ANY,T_ANY,25,DEFAULT_NONE},
{"query_ip_name",F_QUERY_IP_NAME,0,0,0,1,TYPE_STRING,T_OBJECT,T_ANY,T_ANY,T_ANY,25,DEFAULT_NONE},
{"query_ip_number",F_QUERY_IP_NUMBER,0,0,0,1,TYPE_STRING,T_OBJECT,T_ANY,T_ANY,T_ANY,25,DEFAULT_NONE},
{"query_ip_port",F_QUERY_IP_PORT,0,0,0,1,TYPE_NUMBER,T_OBJECT,T_ANY,T_ANY,T_ANY,25,DEFAULT_NONE},
{"query_load_average",F_QUERY_LOAD_AVERAGE,0,0,0,0,TYPE_STRING,T_ANY,T_ANY,T_ANY,T_ANY,0,DEFAULT_NONE},
{"query_notify_fail",F_QUERY_NOTIFY_FAIL,0,0,0,0,TYPE_ANY,T_ANY,T_ANY,T_ANY,T_ANY,0,DEFAULT_NONE},
{"query_num",F_QUERY_NUM,0,0,2,2,TYPE_STRING,T_NUMBER,T_NUMBER,T_ANY,T_ANY,49,0},
{"query_replaced_program",F_QUERY_REPLACED_PROGRAM,0,0,0,1,TYPE_STRING,T_OBJECT,T_ANY,T_ANY,T_ANY,25,DEFAULT_NONE},
{"query_shadowing",F_QUERY_SHADOWING,0,0,1,1,TYPE_OBJECT,T_OBJECT,T_ANY,T_ANY,T_ANY,25,DEFAULT_NONE},
{"query_snoop",F_QUERY_SNOOP,0,0,1,1,TYPE_OBJECT,T_OBJECT,T_ANY,T_ANY,T_ANY,25,DEFAULT_NONE},
{"query_snooping",F_QUERY_SNOOPING,0,0,1,1,TYPE_OBJECT,T_OBJECT,T_ANY,T_ANY,T_ANY,25,DEFAULT_NONE},
{"query_temp",F_QUERY_TEMP,0,0,1,2,TYPE_ANY,T_STRING,T_OBJECT,T_ANY,T_ANY,83,DEFAULT_NONE},
{"query_verb",F_QUERY_VERB,0,0,0,0,TYPE_STRING,T_ANY,T_ANY,T_ANY,T_ANY,0,DEFAULT_NONE},
{"random",F_RANDOM,0,0,1,1,TYPE_NUMBER,T_NUMBER,T_ANY,T_ANY,T_ANY,18,DEFAULT_NONE},
{"read_buffer",F_READ_BUFFER,0,0,1,3,TYPE_ANY,T_STRING|T_BUFFER,T_NUMBER,T_NUMBER,T_ANY,170,DEFAULT_NONE},
{"read_bytes",F_READ_BYTES,0,0,1,3,TYPE_STRING,T_STRING,T_NUMBER,T_NUMBER,T_ANY,192,DEFAULT_NONE},
{"read_file",F_READ_FILE,0,0,1,3,TYPE_STRING,T_STRING,T_NUMBER,T_NUMBER,T_ANY,192,DEFAULT_NONE},
{"real_time",F_REAL_TIME,0,0,0,0,TYPE_NUMBER,T_ANY,T_ANY,T_ANY,T_ANY,0,DEFAULT_NONE},
{"receive",F_RECEIVE,0,0,1,1,TYPE_NOVALUE,T_STRING|T_BUFFER,T_ANY,T_ANY,T_ANY,118,DEFAULT_NONE},
{"reclaim_objects",F_RECLAIM_OBJECTS,0,0,0,0,TYPE_NUMBER,T_ANY,T_ANY,T_ANY,T_ANY,0,DEFAULT_NONE},
{"refs",F_REFS,0,0,1,1,TYPE_NUMBER,T_ANY,T_ANY,T_ANY,T_ANY,8,DEFAULT_NONE},
{"reg_assoc",F_REG_ASSOC,0,0,3,4,TYPE_MOD_ARRAY|TYPE_ANY,T_STRING,T_ARRAY,T_ARRAY,T_ANY,158,DEFAULT_NONE},
{"regexp",F_REGEXP,0,0,2,3,TYPE_ANY,T_STRING|T_ARRAY,T_STRING,T_NUMBER,T_ANY,151,DEFAULT_NONE},
{"reload_object",F_RELOAD_OBJECT,0,0,1,1,TYPE_NOVALUE,T_OBJECT,T_ANY,T_ANY,T_ANY,25,DEFAULT_NONE},
{"remove_action",F_REMOVE_ACTION,0,0,2,2,TYPE_NUMBER,T_STRING,T_STRING,T_ANY,T_ANY,27,DEFAULT_NONE},
{"remove_ansi",F_REMOVE_ANSI,0,0,1,1,TYPE_STRING,T_STRING,T_ANY,T_ANY,T_ANY,20,DEFAULT_NONE},
{"remove_bg_ansi",F_REMOVE_BG_ANSI,0,0,1,1,TYPE_STRING,T_STRING,T_ANY,T_ANY,T_ANY,20,DEFAULT_NONE},
{"remove_call_out",F_REMOVE_CALL_OUT,0,0,0,1,TYPE_NUMBER,T_NUMBER|T_STRING,T_ANY,T_ANY,T_ANY,133,DEFAULT_NONE},
{"remove_charmode",F_REMOVE_CHARMODE,0,0,1,1,TYPE_NUMBER,T_OBJECT,T_ANY,T_ANY,T_ANY,25,DEFAULT_NONE},
{"remove_get_char",F_REMOVE_GET_CHAR,0,0,1,1,TYPE_NUMBER,T_OBJECT,T_ANY,T_ANY,T_ANY,25,DEFAULT_NONE},
{"remove_input_to",F_REMOVE_INPUT_TO,0,0,0,1,TYPE_NOVALUE,T_OBJECT,T_ANY,T_ANY,T_ANY,25,DEFAULT_NONE},
{"remove_interactive",F_REMOVE_INTERACTIVE,0,0,1,1,TYPE_NUMBER,T_OBJECT,T_ANY,T_ANY,T_ANY,25,DEFAULT_NONE},
{"remove_shadow",F_REMOVE_SHADOW,0,0,1,1,TYPE_NUMBER,T_OBJECT,T_ANY,T_ANY,T_ANY,25,DEFAULT_NONE},
{"rename",F_RENAME,0,0,2,2,TYPE_NUMBER,T_STRING,T_STRING,T_ANY,T_ANY,27,DEFAULT_NONE},
{"repeat_string",F_REPEAT_STRING,0,0,2,2,TYPE_STRING,T_STRING,T_NUMBER,T_ANY,T_ANY,102,DEFAULT_NONE},
{"replace_program",F_REPLACE_PROGRAM,0,0,1,1,TYPE_NOVALUE,T_STRING,T_ANY,T_ANY,T_ANY,20,DEFAULT_NONE},
{"replace_string",F_REPLACE_STRING,0,0,3,-1,TYPE_STRING,T_STRING,T_STRING,T_STRING,T_ANY,95,DEFAULT_NONE},
{"replaceable",F_REPLACEABLE,0,0,1,2,TYPE_NUMBER,T_OBJECT,T_ARRAY,T_ANY,T_ANY,328,DEFAULT_NONE},
{"request_term_size",F_REQUEST_TERM_SIZE,0,0,0,1,TYPE_NOVALUE,T_NUMBER,T_ANY,T_ANY,T_ANY,18,DEFAULT_NONE},
{"request_term_type",F_REQUEST_TERM_TYPE,0,0,0,0,TYPE_NOVALUE,T_ANY,T_ANY,T_ANY,T_ANY,0,DEFAULT_NONE},
{"reset_eval_cost",F_SET_EVAL_LIMIT | F_ALIAS_FLAG,0,0,1,1,TYPE_NUMBER,T_NUMBER,T_ANY,T_ANY,T_ANY,18,0},
{"resolve",F_RESOLVE,0,0,2,2,TYPE_NUMBER,T_STRING,T_STRING|T_FUNCTION,T_ANY,T_ANY,249,DEFAULT_NONE},
{"restore_from_string",F_RESTORE_FROM_STRING,0,0,2,2,TYPE_NOVALUE,T_STRING,T_NUMBER,T_ANY,T_ANY,102,0},
{"restore_object",F_RESTORE_OBJECT,0,0,1,2,TYPE_NUMBER,T_STRING,T_NUMBER,T_ANY,T_ANY,102,DEFAULT_NONE},
{"restore_variable",F_RESTORE_VARIABLE,0,0,1,1,TYPE_ANY,T_STRING,T_ANY,T_ANY,T_ANY,20,DEFAULT_NONE},
{"rm",F_RM,0,0,1,1,TYPE_NUMBER,T_STRING,T_ANY,T_ANY,T_ANY,20,DEFAULT_NONE},
{"rmdir",F_RMDIR,0,0,1,1,TYPE_NUMBER,T_STRING,T_ANY,T_ANY,T_ANY,20,DEFAULT_NONE},
{"round",F_ROUND,0,0,1,1,TYPE_REAL,T_REAL,T_ANY,T_ANY,T_ANY,77,DEFAULT_NONE},
{"rusage",F_RUSAGE,0,0,0,0,TYPE_MAPPING,T_ANY,T_ANY,T_ANY,T_ANY,0,DEFAULT_NONE},
{"save_object",F_SAVE_OBJECT,0,0,0,2,TYPE_ANY,T_STRING|T_NUMBER,T_NUMBER,T_ANY,T_ANY,106,DEFAULT_NONE},
{"save_variable",F_SAVE_VARIABLE,0,0,1,1,TYPE_STRING,T_ANY,T_ANY,T_ANY,T_ANY,8,DEFAULT_NONE},
{"say",F_SAY,0,0,1,2,TYPE_NOVALUE,T_STRING,T_OBJECT|T_ARRAY,T_ANY,T_ANY,66,DEFAULT_NONE},
{"send_nullbyte",F_SEND_NULLBYTE,0,0,1,1,TYPE_NUMBER,T_OBJECT,T_ANY,T_ANY,T_ANY,25,DEFAULT_NONE},
{"set",F_SET,0,0,2,3,TYPE_ANY,T_STRING,T_ANY,T_OBJECT,T_ANY,271,DEFAULT_NONE},
{"set_bit",F_SET_BIT,0,0,2,2,TYPE_STRING,T_STRING,T_NUMBER,T_ANY,T_ANY,102,DEFAULT_NONE},
{"set_eval_limit",F_SET_EVAL_LIMIT,0,0,1,1,TYPE_NUMBER,T_NUMBER,T_ANY,T_ANY,T_ANY,18,DEFAULT_NONE},
{"set_heart_beat",F_SET_HEART_BEAT,0,0,1,1,TYPE_NOVALUE,T_NUMBER,T_ANY,T_ANY,T_ANY,18,DEFAULT_NONE},
{"set_heartbeat_interval",F_SET_HEARTBEAT_INTERVAL,0,0,1,1,TYPE_NOVALUE,T_NUMBER,T_ANY,T_ANY,T_ANY,18,DEFAULT_NONE},
{"set_hide",F_SET_HIDE,0,0,1,1,TYPE_NOVALUE,T_NUMBER,T_ANY,T_ANY,T_ANY,18,DEFAULT_NONE},
{"set_living_name",F_SET_LIVING_NAME,0,0,1,1,TYPE_NOVALUE,T_STRING,T_ANY,T_ANY,T_ANY,20,DEFAULT_NONE},
{"set_reset",F_SET_RESET,0,0,1,2,TYPE_NOVALUE,T_OBJECT,T_NUMBER,T_ANY,T_ANY,204,DEFAULT_NONE},
{"set_temp",F_SET_TEMP,0,0,2,3,TYPE_ANY,T_STRING,T_ANY,T_OBJECT,T_ANY,271,DEFAULT_NONE},
{"seteuid",F_SETEUID,0,0,1,1,TYPE_NUMBER,T_STRING|T_NUMBER,T_ANY,T_ANY,T_ANY,106,DEFAULT_NONE},
{"shadow",F_SHADOW,0,0,2,2,TYPE_OBJECT,T_OBJECT,T_NUMBER,T_ANY,T_ANY,204,1},
{"shallow_inherit_list",F_SHALLOW_INHERIT_LIST,0,0,1,1,TYPE_MOD_ARRAY|TYPE_STRING,T_OBJECT,T_ANY,T_ANY,T_ANY,25,DEFAULT_THIS_OBJECT},
{"shout",F_SHOUT,0,0,1,1,TYPE_NOVALUE,T_STRING,T_ANY,T_ANY,T_ANY,20,DEFAULT_NONE},
{"shuffle",F_SHUFFLE,0,0,1,1,TYPE_MOD_ARRAY|TYPE_ANY,T_ARRAY,T_ANY,T_ANY,T_ANY,5,DEFAULT_NONE},
{"shutdown",F_SHUTDOWN,0,0,0,1,TYPE_NOVALUE,T_NUMBER,T_ANY,T_ANY,T_ANY,18,DEFAULT_NONE},
{"sin",F_SIN,0,0,1,1,TYPE_REAL,T_REAL,T_ANY,T_ANY,T_ANY,77,DEFAULT_NONE},
{"sizeof",F_SIZEOF,0,0,1,1,TYPE_NUMBER,T_ANY,T_ANY,T_ANY,T_ANY,8,DEFAULT_NONE},
{"snoop",F_SNOOP,0,0,1,2,TYPE_OBJECT,T_OBJECT,T_OBJECT,T_ANY,T_ANY,198,DEFAULT_NONE},
{"socket_accept",F_SOCKET_ACCEPT,0,0,3,3,TYPE_NUMBER,T_NUMBER,T_STRING|T_FUNCTION,T_STRING|T_FUNCTION,T_ANY,341,DEFAULT_NONE},
{"socket_acquire",F_SOCKET_ACQUIRE,0,0,4,4,TYPE_NUMBER,T_NUMBER,T_STRING|T_FUNCTION,T_STRING|T_FUNCTION,T_STRING|T_FUNCTION,372,DEFAULT_NONE},
{"socket_address",F_SOCKET_ADDRESS,0,0,2,2,TYPE_STRING,T_NUMBER|T_OBJECT,T_NUMBER,T_ANY,T_ANY,383,0},
{"socket_bind",F_SOCKET_BIND,0,0,2,3,TYPE_NUMBER,T_NUMBER,T_NUMBER,T_STRING,T_ANY,107,DEFAULT_NONE},
{"socket_close",F_SOCKET_CLOSE,0,0,1,1,TYPE_NUMBER,T_NUMBER,T_ANY,T_ANY,T_ANY,18,DEFAULT_NONE},
{"socket_connect",F_SOCKET_CONNECT,0,0,4,4,TYPE_NUMBER,T_NUMBER,T_STRING,T_STRING|T_FUNCTION,T_STRING|T_FUNCTION,349,DEFAULT_NONE},
{"socket_create",F_SOCKET_CREATE,0,0,2,3,TYPE_NUMBER,T_NUMBER,T_STRING|T_FUNCTION,T_STRING|T_FUNCTION,T_ANY,341,DEFAULT_NONE},
{"socket_error",F_SOCKET_ERROR,0,0,1,1,TYPE_STRING,T_NUMBER,T_ANY,T_ANY,T_ANY,18,DEFAULT_NONE},
{"socket_listen",F_SOCKET_LISTEN,0,0,2,2,TYPE_NUMBER,T_NUMBER,T_STRING|T_FUNCTION,T_ANY,T_ANY,51,DEFAULT_NONE},
{"socket_release",F_SOCKET_RELEASE,0,0,3,3,TYPE_NUMBER,T_NUMBER,T_OBJECT,T_STRING|T_FUNCTION,T_ANY,365,DEFAULT_NONE},
{"socket_status",F_SOCKET_STATUS,0,0,0,1,TYPE_MOD_ARRAY|TYPE_ANY,T_NUMBER,T_ANY,T_ANY,T_ANY,18,DEFAULT_NONE},
{"socket_write",F_SOCKET_WRITE,0,0,2,3,TYPE_NUMBER,T_NUMBER,T_ANY,T_STRING,T_ANY,359,DEFAULT_NONE},
{"sort_array",F_SORT_ARRAY,0,0,2,-1,TYPE_MOD_ARRAY|TYPE_ANY,T_ARRAY,T_NUMBER|T_STRING|T_FUNCTION,T_ANY,T_ANY,208,DEFAULT_NONE},
{"sprintf",F_SPRINTF,0,0,1,-1,TYPE_STRING,T_STRING,T_ANY,T_ANY,T_ANY,20,DEFAULT_NONE},
{"sqrt",F_SQRT,0,0,1,1,TYPE_REAL,T_REAL|T_NUMBER,T_ANY,T_ANY,T_ANY,17,DEFAULT_NONE},
{"start_request_term_type",F_START_REQUEST_TERM_TYPE,0,0,0,0,TYPE_NOVALUE,T_ANY,T_ANY,T_ANY,T_ANY,0,DEFAULT_NONE},
{"stat",F_STAT,0,0,2,2,TYPE_MOD_ARRAY|TYPE_ANY,T_STRING,T_NUMBER,T_ANY,T_ANY,102,0},
{"store_class_member",F_STORE_CLASS_MEMBER,0,0,3,3,TYPE_ANY,T_ANY,T_NUMBER,T_ANY,T_ANY,164,DEFAULT_NONE},
{"store_variable",F_STORE_VARIABLE,0,0,2,3,TYPE_NOVALUE,T_STRING,T_ANY,T_OBJECT,T_ANY,271,DEFAULT_NONE},
{"strcmp",F_STRCMP,0,0,2,2,TYPE_NUMBER,T_STRING,T_STRING,T_ANY,T_ANY,27,DEFAULT_NONE},
{"string_difference",F_STRING_DIFFERENCE,0,0,2,2,TYPE_NUMBER,T_STRING,T_STRING,T_ANY,T_ANY,27,DEFAULT_NONE},
{"stringp",F_STRINGP,0,0,1,1,TYPE_NUMBER,T_ANY,T_ANY,T_ANY,T_ANY,8,DEFAULT_NONE},
{"strlen",F_SIZEOF | F_ALIAS_FLAG,0,0,1,1,TYPE_NUMBER,T_STRING,T_ANY,T_ANY,T_ANY,20,DEFAULT_NONE},
{"strsrch",F_STRSRCH,0,0,3,3,TYPE_NUMBER,T_STRING,T_STRING|T_NUMBER,T_NUMBER,T_ANY,111,0},
{"strtobuf",F_STRTOBUF,0,0,1,1,TYPE_BUFFER,T_STRING,T_ANY,T_ANY,T_ANY,20,DEFAULT_NONE},
{"strwidth",F_SIZEOF | F_ALIAS_FLAG,0,0,1,1,TYPE_NUMBER,T_STRING,T_ANY,T_ANY,T_ANY,20,DEFAULT_NONE},
{"tan",F_TAN,0,0,1,1,TYPE_REAL,T_REAL,T_ANY,T_ANY,T_ANY,77,DEFAULT_NONE},
{"tell_object",F_TELL_OBJECT,0,0,2,2,TYPE_NOVALUE,T_OBJECT,T_STRING,T_ANY,T_ANY,25,DEFAULT_NONE},
{"tell_room",F_TELL_ROOM,0,0,2,3,TYPE_NOVALUE,T_OBJECT|T_STRING,T_STRING|T_OBJECT|T_NUMBER|T_REAL,T_OBJECT|T_ARRAY,T_ANY,71,DEFAULT_NONE},
{"terminal_colour",F_TERMINAL_COLOUR,0,0,2,4,TYPE_STRING,T_STRING,T_MAPPING,T_NUMBER,T_NUMBER,320,DEFAULT_NONE},
{"test_bit",F_TEST_BIT,0,0,2,2,TYPE_NUMBER,T_STRING,T_NUMBER,T_ANY,T_ANY,102,DEFAULT_NONE},
{"this_interactive",F_THIS_PLAYER | F_ALIAS_FLAG,0,0,1,1,TYPE_OBJECT,T_NUMBER,T_ANY,T_ANY,T_ANY,18,1},
{"this_object",F__THIS_OBJECT | F_ALIAS_FLAG,0,0,0,0,TYPE_OBJECT,T_ANY,T_ANY,T_ANY,T_ANY,0,DEFAULT_NONE},
{"this_player",F_THIS_PLAYER,0,0,1,1,TYPE_OBJECT,T_NUMBER,T_ANY,T_ANY,T_ANY,18,0},
{"this_user",F_THIS_PLAYER | F_ALIAS_FLAG,0,0,1,1,TYPE_OBJECT,T_NUMBER,T_ANY,T_ANY,T_ANY,18,0},
{"throw",F_THROW,0,0,1,1,TYPE_NOVALUE,T_ANY,T_ANY,T_ANY,T_ANY,8,DEFAULT_NONE},
{"time",F_TIME,0,0,0,0,TYPE_NUMBER,T_ANY,T_ANY,T_ANY,T_ANY,0,DEFAULT_NONE},
{"to_float",F__TO_FLOAT | F_ALIAS_FLAG,0,0,1,1,TYPE_REAL,T_STRING|T_REAL|T_NUMBER,T_ANY,T_ANY,T_ANY,16,DEFAULT_NONE},
{"to_int",F__TO_INT | F_ALIAS_FLAG,0,0,1,1,TYPE_NUMBER,T_STRING|T_REAL|T_NUMBER|T_BUFFER,T_ANY,T_ANY,T_ANY,11,DEFAULT_NONE},
{"typeof",F_TYPEOF,0,0,1,1,TYPE_STRING,T_ANY,T_ANY,T_ANY,T_ANY,8,DEFAULT_NONE},
{"uncompress",F_UNCOMPRESS,0,0,1,1,TYPE_BUFFER,T_STRING|T_BUFFER,T_ANY,T_ANY,T_ANY,118,DEFAULT_NONE},
{"uncompress_file",F_UNCOMPRESS_FILE,0,0,1,2,TYPE_NUMBER,T_STRING,T_STRING,T_ANY,T_ANY,27,DEFAULT_NONE},
{"undefinedp",F_UNDEFINEDP,0,0,1,1,TYPE_NUMBER,T_ANY,T_ANY,T_ANY,T_ANY,8,DEFAULT_NONE},
{"unique_array",F_UNIQUE_ARRAY,0,0,2,3,TYPE_MOD_ARRAY|TYPE_ANY,T_ARRAY,T_STRING|T_FUNCTION,T_ANY,T_ANY,31,DEFAULT_NONE},
{"unique_mapping",F_UNIQUE_MAPPING,0,0,2,-1,TYPE_MAPPING,T_ARRAY,T_STRING|T_FUNCTION,T_ANY,T_ANY,215,DEFAULT_NONE},
{"upper_case",F_UPPER_CASE,0,0,1,1,TYPE_STRING,T_STRING,T_ANY,T_ANY,T_ANY,20,DEFAULT_NONE},
{"uptime",F_UPTIME,0,0,0,0,TYPE_NUMBER,T_ANY,T_ANY,T_ANY,T_ANY,0,DEFAULT_NONE},
{"userp",F_USERP,0,0,1,1,TYPE_NUMBER,T_OBJECT,T_ANY,T_ANY,T_ANY,25,DEFAULT_NONE},
{"users",F_USERS,0,0,0,0,TYPE_MOD_ARRAY|TYPE_OBJECT,T_ANY,T_ANY,T_ANY,T_ANY,0,DEFAULT_NONE},
{"values",F_VALUES,0,0,1,1,TYPE_MOD_ARRAY|TYPE_ANY,T_MAPPING,T_ANY,T_ANY,T_ANY,141,DEFAULT_NONE},
{"variables",F_VARIABLES,0,0,2,2,TYPE_MOD_ARRAY|TYPE_ANY,T_OBJECT,T_NUMBER,T_ANY,T_ANY,204,0},
{"virtualp",F_VIRTUALP,0,0,1,1,TYPE_NUMBER,T_OBJECT,T_ANY,T_ANY,T_ANY,25,DEFAULT_THIS_OBJECT},
{"wizardp",F_WIZARDP,0,0,1,1,TYPE_NUMBER,T_OBJECT,T_ANY,T_ANY,T_ANY,25,DEFAULT_NONE},
{"write",F_WRITE,0,0,1,1,TYPE_NOVALUE,T_ANY,T_ANY,T_ANY,T_ANY,8,DEFAULT_NONE},
{"write_buffer",F_WRITE_BUFFER,0,0,3,3,TYPE_NUMBER,T_STRING|T_BUFFER,T_NUMBER,T_STRING|T_BUFFER|T_NUMBER,T_ANY,177,DEFAULT_NONE},
{"write_bytes",F_WRITE_BYTES,0,0,3,3,TYPE_NUMBER,T_STRING,T_NUMBER,T_STRING,T_ANY,154,DEFAULT_NONE},
{"write_file",F_WRITE_FILE,0,0,3,3,TYPE_NUMBER,T_STRING,T_STRING,T_NUMBER,T_ANY,186,0},
{"zonetime",F_ZONETIME,0,0,2,2,TYPE_STRING,T_STRING,T_NUMBER,T_ANY,T_ANY,102,DEFAULT_NONE},

};
int efun_arg_types[] = {
TYPE_OBJECT,TYPE_STRING,TYPE_MOD_ARRAY|TYPE_OBJECT,0,
TYPE_STRING,TYPE_MOD_ARRAY|TYPE_ANY,0,
0,
TYPE_ANY,0,
0,
TYPE_STRING,TYPE_REAL,TYPE_NUMBER,TYPE_BUFFER,0,
TYPE_STRING,TYPE_REAL,TYPE_NUMBER,0,
TYPE_STRING,0,
0,
TYPE_FUNCTION,0,
TYPE_OBJECT,0,
TYPE_STRING,0,
TYPE_STRING,0,
TYPE_MOD_ARRAY|TYPE_ANY,0,
TYPE_STRING,TYPE_FUNCTION,0,
TYPE_ANY,0,
TYPE_STRING,TYPE_FUNCTION,0,
TYPE_NUMBER,0,
0,
TYPE_ANY,0,
TYPE_STRING,TYPE_MOD_ARRAY|TYPE_ANY,0,
TYPE_NUMBER,0,
TYPE_NUMBER,0,
TYPE_STRING,TYPE_FUNCTION,0,
0,
TYPE_OBJECT,TYPE_MOD_ARRAY|TYPE_OBJECT,TYPE_FUNCTION,0,
TYPE_FUNCTION,0,
TYPE_OBJECT,TYPE_STRING,0,
TYPE_STRING,0,
TYPE_OBJECT,TYPE_MOD_ARRAY|TYPE_OBJECT,0,
TYPE_OBJECT,TYPE_STRING,0,
TYPE_STRING,TYPE_OBJECT,TYPE_NUMBER,TYPE_REAL,0,
TYPE_OBJECT,TYPE_MOD_ARRAY|TYPE_OBJECT,0,
TYPE_OBJECT,TYPE_STRING,0,
TYPE_OBJECT,0,
TYPE_STRING,TYPE_FUNCTION,0,
TYPE_STRING,TYPE_MOD_ARRAY|TYPE_STRING,0,
TYPE_NUMBER,0,
TYPE_STRING,0,
TYPE_STRING,0,
TYPE_STRING,0,
0,
TYPE_STRING,0,
TYPE_NUMBER,0,
TYPE_STRING,TYPE_NUMBER,0,
TYPE_NUMBER,0,
TYPE_STRING,0,
TYPE_STRING,TYPE_NUMBER,0,
TYPE_NUMBER,0,
TYPE_STRING,TYPE_BUFFER,0,
TYPE_ANY,0,
TYPE_ANY,0,
TYPE_STRING,TYPE_MOD_ARRAY|TYPE_STRING,TYPE_OBJECT,TYPE_MOD_ARRAY|TYPE_OBJECT,0,
TYPE_OBJECT,TYPE_MOD_ARRAY|TYPE_OBJECT,0,
TYPE_NUMBER,TYPE_STRING,0,
TYPE_NUMBER,TYPE_MOD_ARRAY|TYPE_ANY,0,
TYPE_ANY,0,
TYPE_MAPPING,0,
TYPE_MAPPING,0,
TYPE_ANY,0,
TYPE_MAPPING,0,
TYPE_STRING,0,
TYPE_STRING,TYPE_MOD_ARRAY|TYPE_STRING,0,
TYPE_STRING,0,
TYPE_NUMBER,0,
TYPE_STRING,0,
TYPE_MOD_ARRAY|TYPE_STRING,0,
TYPE_MOD_ARRAY|TYPE_ANY,0,
TYPE_ANY,0,
TYPE_NUMBER,0,
TYPE_ANY,0,
TYPE_STRING,TYPE_BUFFER,0,
TYPE_NUMBER,0,
TYPE_NUMBER,0,
TYPE_STRING,TYPE_BUFFER,0,
TYPE_NUMBER,0,
TYPE_STRING,TYPE_BUFFER,TYPE_NUMBER,0,
TYPE_STRING,0,
TYPE_STRING,0,
TYPE_NUMBER,0,
TYPE_STRING,0,
TYPE_NUMBER,0,
TYPE_NUMBER,0,
TYPE_OBJECT,0,
TYPE_OBJECT,0,
TYPE_STRING,0,
TYPE_OBJECT,0,
TYPE_NUMBER,0,
TYPE_MOD_ARRAY|TYPE_ANY,0,
TYPE_NUMBER,TYPE_STRING,TYPE_FUNCTION,0,
0,
TYPE_MOD_ARRAY|TYPE_ANY,0,
TYPE_STRING,TYPE_FUNCTION,0,
0,
TYPE_STRING,0,
TYPE_STRING,TYPE_NUMBER,0,
TYPE_STRING,TYPE_NUMBER,0,
TYPE_NUMBER,0,
TYPE_NUMBER,0,
TYPE_STRING,TYPE_MOD_ARRAY|TYPE_ANY,TYPE_MAPPING,0,
TYPE_STRING,TYPE_FUNCTION,0,
0,
TYPE_STRING,TYPE_MAPPING,TYPE_MOD_ARRAY|TYPE_ANY,0,
TYPE_STRING,TYPE_FUNCTION,0,
0,
TYPE_STRING,0,
TYPE_STRING,TYPE_FUNCTION,0,
TYPE_FUNCTION,TYPE_OBJECT,0,
TYPE_ANY,0,
TYPE_STRING,0,
TYPE_ANY,0,
TYPE_STRING,0,
TYPE_STRING,0,
TYPE_STRING,0,
TYPE_NUMBER,0,
TYPE_STRING,0,
TYPE_ANY,0,
TYPE_OBJECT,0,
TYPE_STRING,0,
TYPE_NUMBER,0,
TYPE_OBJECT,0,
TYPE_REAL,TYPE_NUMBER,0,
TYPE_REAL,TYPE_NUMBER,0,
TYPE_MOD_ARRAY|TYPE_NUMBER,TYPE_MOD_ARRAY|TYPE_REAL,0,
TYPE_MOD_ARRAY|TYPE_NUMBER,TYPE_MOD_ARRAY|TYPE_REAL,0,
TYPE_MOD_ARRAY|TYPE_NUMBER,TYPE_MOD_ARRAY|TYPE_REAL,0,
TYPE_OBJECT,0,
0,
TYPE_STRING,0,
TYPE_ANY,0,
0,
TYPE_NUMBER,0,
TYPE_STRING,TYPE_MOD_ARRAY|TYPE_STRING,0,
TYPE_STRING,TYPE_FUNCTION,0,
TYPE_STRING,TYPE_FUNCTION,0,
TYPE_STRING,TYPE_FUNCTION,0,
TYPE_STRING,0,
TYPE_MAPPING,0,
TYPE_NUMBER,0,
TYPE_NUMBER,0,
TYPE_OBJECT,0,
TYPE_MOD_ARRAY|TYPE_STRING,0,
TYPE_OBJECT,TYPE_MOD_ARRAY|TYPE_OBJECT,0,
TYPE_STRING,0,
0,
TYPE_STRING,TYPE_OBJECT,0,
TYPE_NUMBER,0,
TYPE_STRING,TYPE_FUNCTION,0,
TYPE_STRING,TYPE_FUNCTION,0,
TYPE_NUMBER,0,
TYPE_STRING,0,
TYPE_STRING,TYPE_FUNCTION,0,
TYPE_STRING,TYPE_FUNCTION,0,
TYPE_NUMBER,0,
TYPE_ANY,0,
TYPE_STRING,0,
TYPE_NUMBER,0,
TYPE_OBJECT,0,
TYPE_STRING,TYPE_FUNCTION,0,
TYPE_NUMBER,0,
TYPE_STRING,TYPE_FUNCTION,0,
TYPE_STRING,TYPE_FUNCTION,0,
TYPE_STRING,TYPE_FUNCTION,0,
TYPE_NUMBER,TYPE_OBJECT,0,
TYPE_NUMBER,0,
TYPE_STRING,0,
TYPE_FUNCTION,0,
TYPE_STRING,0,
TYPE_STRING,0,
TYPE_NUMBER,0,
TYPE_FUNCTION,0,
};
