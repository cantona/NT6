inherit ROOM;

void create()
{
        set("short", "天蠶洞");
        set("long", @LONG
這裡是天山蠶洞，只見洞內非常寬敞，洞頂可看見藍天白
雲，聽說這裡是天蠶繁殖的地方。

LONG);
        set("exits", ([
                "out" : __DIR__"tianroad6",
        ]));
        set("outdoors", "xingxiu");
        // 可打獵標志
        set("can_hunting", 1);
        set("quarry", ([
             "can"       :  20,
             "tiancan"   :  50,
             "zhang"     :  40,
        ]));

        setup();
}

