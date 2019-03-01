// Room: /d/yueyang/longxianjing.c
// Last Modifyed by Winder on Dec. 4 2001

inherit ROOM;

void create()
{
        set("short", "龍涎井");
        set("long", @LONG
龍涎井在龍舌山下，這裡的井水清澈純凈，四時不涸，是龍舌頭上
面一點點滴下的涎水，故稱“龍涎井”。井內赭黃色巖石形象龍舌，泉
水從巖石上注入井內，一點一滴，好似涎水。過去井水終年不涸，清澈
見底，冬暖夏涼。故老相傳，用龍涎井的水泡君山茶，喝了百病皆除，
長生不老。古人信以為真，遠道乘舟來取龍涎者絡繹不絕。《君山茶歌
》雲：“試挹龍涎烹雀舌，烹來長似君山色”，足見珍貴。
    距井口三尺遠處，立一對雕龍柱坊，高近丈，門寬四尺，門楣上鐫
刻“龍涎井”三個蒼勁有力的正楷大字。
LONG );
        set("outdoors", "dongting");
        set("no_clean_up", 0);
        set("exits", ([
                "south"   : __DIR__"longkou",
                "northup" : __DIR__"feilaizhong",
        ]));
        set("coor/x", -1720);
        set("coor/y", 2300);
        set("coor/z", -20);
        setup();
        replace_program(ROOM);
}