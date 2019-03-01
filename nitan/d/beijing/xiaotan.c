// xiaotan.c

inherit ROOM;

void create()
{
        set("short", "小攤");
        set("long", @LONG
這是一臨時搭成的小攤，生意卻非常興隆。路人都愛在這裡落腳，
你可以在這裡打聽到京城的奇聞逸趣。小二匆匆忙忙地接待著南來北
往的客人。樹蔭下擺著幾張小木桌，桌旁坐滿了各種各樣的遊人。
LONG );
        set("no_sleep_room",1);
        set("objects", ([
                "/d/beijing/npc/xiaoer" : 1,
                "/d/huashan/npc/youke" :2,
        ]));
        set("exits", ([
                "east" : "/d/beijing/road8",
        ]));
	set("coor/x", -2780);
	set("coor/y", 7570);
	set("coor/z", 0);
	setup();
}

int valid_leave(object me, string dir)
{
        if ((dir == "east") && present("mian", this_player()) &&
            objectp(present("xiao er", environment(me))))
                return notify_fail("\n小二追出來說道：這位客官，吃面還想連碗端走啊？\n");

        return ::valid_leave(me,dir);
}