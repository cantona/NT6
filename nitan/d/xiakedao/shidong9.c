// shidong9.c 石洞

inherit ROOM;

void create()
{
        set("short", "石洞");
        set("long", @LONG
這是一個很小的石洞，兩邊點着紅燭，光線雖暗，卻也能辯得
出方向。走着走着，你隱約看見在前面有一個身影，只見他身穿青
色長衫，眼視前方，一副唯我獨尊的樣子。
LONG );
        set("exits", ([
                "west" : __DIR__"shidong10",
                "east" : __DIR__"yadi",
        ]));
        set("objects",([
                __DIR__"npc/baishou" : 1,
        ]));
        set("coor/x", -3100);
        set("coor/y", -22070);
        set("coor/z", 0);
        setup();
}

int valid_leave(object me, string dir)
{

        if (  (dir == "west")
            && (query("shen", me)<10000 )
            || (query("PKS", me)>10 )
           && objectp(present("bai shou",environment(me))) )
        return notify_fail
                ("白首把手一攔：你這種邪派人物，還敢到這來，快滾! \n");
        return ::valid_leave(me, dir);
}