// /d/xingxiu/house.c
// Last Modified by winder on Feb. 28 2001

inherit ROOM;

void create()
{
        set("short", "巴依家院");
        set("long", @LONG
這是一個巴依家的庭院。門口大樹的樹蔭投到院子裏，讓人覺得很
涼快。院子東面是巴依的客廳，西邊就是伊犁鎮大街。
LONG
        );
        set("exits", ([ 
            "west" : __DIR__"yili",
            "east" : __DIR__"house1",
        ]));
        set("objects", ([
                __DIR__"npc/kid": 1,
                __DIR__"npc/bayi": 1
        ]) );
//        set("no_clean_up", 0);
        set("outdoors", "xiyu");

        set("coor/x", -38900);
        set("coor/y", 13000);
        set("coor/z", 0);
        setup();
}

int valid_leave(object me, string dir)
{
        if (!wizardp(me) &&
                objectp(present("bayi", environment(me))) && 
                dir == "east")
                return notify_fail("巴依説：我把阿凡提關在我的客廳裏了，誰也不許進去。\n");
        return ::valid_leave(me, dir);
}