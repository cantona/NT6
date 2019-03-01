inherit ROOM;

void create()
{
        set("short", "上山小路");
        set("long", @LONG
這是一條陡峭的上山小路，兩旁都是帶刺的荊棘，地上是稀
鬆的黃土和小石子，一不小心準摔跟鬥。
LONG
        );
        set("exits", ([ /* sizeof() == 2 */
  "northup" : __DIR__"shangpo5",
  "southdown" : __DIR__"shangpo3",
]));

        set("outdoors", "tangmen");
        setup();
}

int valid_leave(object me, string dir)
{
        int sk;

        if(!userp(me) || (dir != "northup"))
                return ::valid_leave(me, dir);

        sk = me->query_skill("dodge", 1);

        if(random(40) > sk)
        {
                me->receive_damage("qi", 25);
                return notify_fail("你一個不留神，摔了個大馬爬。\n");
        }

        return ::valid_leave(me, dir);
}
