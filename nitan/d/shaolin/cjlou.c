// Room: /d/shaolin/cjlou.c
// Date: YZC 96/01/19

inherit ROOM;

void create()
{
        set("short", "藏經閣一樓");
        set("long", @LONG
不愧為中原佛法的總源，少林寺此處藏經之富，天下罕有其匹。
這裏都是密密麻麻，高及頂棚的書架，書架間僅有容身一人通行的空
隙。幾排大書架中間，間隔地放着數丈長的書桌。目光及處，你看到
桌上放了幾本佛經。
LONG );
        set("exits", ([
                "east" : __DIR__"zhulin5",
                "up" : __DIR__"cjlou1",
        ]));
        set("objects",([
                CLASS_D("shaolin") + "/dao-yi" : 1,
                CLASS_D("shaolin") + "/wuming" : 1,
                "d/shaolin/obj/fojing1"+random(2) : 1,
                "d/shaolin/obj/fojing2"+random(2) : 1,
        ]));
        setup();
}

int valid_leave(object me, string dir)
{
        if (! present("shou yu", me) &&
            (objectp(present("daoyi chanshi", environment(me)))))
        {
                if (dir == "up" )
                {
                        return notify_fail("道一説道: 你未經許可，不能上二樓。\n");
                }
        }
        return ::valid_leave(me, dir);
}
