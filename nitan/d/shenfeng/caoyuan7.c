inherit ROOM;

void create()
{
        set("short", "山路");
        set("long", @LONG
山路自東向西，地勢漸平。雲中有幾頭蒼鷹在低低的盤旋
遨翔，仿佛將行人當作了獵物。路面舖著小石子，道兩旁的灌
木越來越少，驕陽似火，令人真想找個地方休息一下。
LONG);
        set("outdoors", "gaochang");
        set("exits", ([
                  "north" : "/d/gaochang/shulin1",
                  "westdown" : __DIR__"shamo1",
                  "eastdown" : __DIR__"caoyuan6",
        ]));
        setup();
}

int valid_leave(object me, string dir)
{
        if (! userp(me) && dir == "north")
                return notify_fail("高昌迷□NPC立入禁止。\n");
        return ::valid_leave(me, dir);
}