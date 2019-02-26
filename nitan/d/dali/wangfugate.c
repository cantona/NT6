//Room: /d/dali/wangfugate.c
//Date: June. 29 1998 by Java

inherit ROOM;

void create()
{
        set("short","王府大門");
        set("long", @LONG
你正站在一座豪華的府門前，門前有兩隻極大的石獅子，門上高
懸一塊橫匾，上書「鎮南王府」四個金字。門口站着兩排侍衞，身着
錦衣，手執鋼刀，氣宇軒昂。
LONG );
        set("objects", ([
                CLASS_D("duan")+"/first" :  1,
           CLASS_D("dali")+"/chuwanli": 1,
           "/d/dali/npc/weishi2": 1,
           "/d/dali/npc/weishi1": 2,
        ]));
        set("valid_startroom", 1);
        set("no_sleep_room",1);
        set("outdoors", "daliwang");
        set("exits",([ /* sizeof() == 1 */
            "enter"  : "/d/dali/wfdating",
            "south"  : "/d/dali/wangfulu",
        ]));
	set("coor/x", -19120);
	set("coor/y", -6860);
	set("coor/z", 0);
	setup();
        "/clone/board/dali_b"->foo();
}

int valid_leave(object me, string dir)
{
        object ob;
        if (dir == "enter" && ob = present("chu wanli", this_object()))
                return ob->permit_pass(me, dir);

        return ::valid_leave(me, dir);
}
