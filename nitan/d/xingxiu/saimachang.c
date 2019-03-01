// room: /d/xingxiu/saimachang.c
// Last Modified by winder on Feb. 28 2001

inherit ROOM;

void create()
{
        set("short", "賽馬場");
        set("long", @LONG
這裡是小鎮的賽馬場。場上正在舉行維吾爾族的「姑娘追」表演。
一個小伙子可以找一個姑娘並騎慢馳到一處折返點。去的路上小伙子可
以對姑娘隨便挑逗。回來時姑娘則可以用鞭子抽打小伙子。當然，如果
姑娘喜歡這個小伙子，落鞭就會輕些。否則的話，有小伙子好受的。
LONG );
        set("exits", ([ 
                "southeast" : __DIR__"yili",
        ]));
//        set("no_clean_up", 0);
        set("outdoors", "xiyu");
        set("objects", ([
                __DIR__"npc/alamuhan" : 1,
        ]) );
        set("coor/x", -39100);
        set("coor/y", 13100);
        set("coor/z", 0);
        setup();
        replace_program(ROOM);
}