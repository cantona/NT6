// database.h

// 是否採用永久連接
#define STATIC_LINK
// 是否調試狀態
// #define DEBUG
// 是否允許分站新玩家註冊
// #define REFUSE_NEW_PLAYER

protected mapping all_others_db = ([
        // "61.184.100.7" : "nitan.dx",
]);

protected mapping stations = ([
        "113.31.21.157" : "《泥潭·王者歸來》",
]);

#ifndef DATABASE
nosave string DATABASE               = "mud";
#endif
#ifndef DB_USER
nosave string DB_USER                = "lonely";
#endif
nosave string USER_TABLE             = "users";
nosave string IP_TABLE               = "ip";
nosave string NEWS_TABLE             = "news";
nosave string ITEM_TABLE             = "items";
nosave string MEMBER_TABLE           = "members";
nosave string CARD_TABLE             = "cards";

// 採用的加密算法
nosave string DB_CRYPT               = "PASSWORD";
