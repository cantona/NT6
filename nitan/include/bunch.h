// banghui.h
// 幫會定義文件

// 房間長描述限定
protected nosave int room_desc_l = 52, room_desc_h = 6;

// 房間最大出口數
protected nosave int max_exits = 5;

// 每個房間最多定義的 action 數目
protected nosave int max_action_per_room = 2;

protected nosave mapping r_dir = ([
        "north"         : "south",
        "south"         : "north",
        "west"          : "east",
        "east"          : "west",
        "northwest"     : "southeast",
        "northeast"     : "southweat",
        "southwest"     : "northeast",
        "southeast"     : "northwest",
        "northup"       : "southdown",
        "northdown"     : "southup",
        "southup"       : "northdown",
        "southdown"     : "northup",
        "westup"        : "eastdown",
        "westdown"      : "eastup",
        "eastup"        : "westdown",
        "eastdown"      : "westup",
        "enter"         : "out",
        "out"           : "enter",
]);

protected nosave string vdirs = "north south west east
northwest northeast southwest southeast
northup northdown southup southdown
westup westdown eastup eastdown
enter out";


