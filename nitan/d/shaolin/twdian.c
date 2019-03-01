// Room: /d/shaolin/twdian.c
// Date: YZC 96/01/19

inherit ROOM;

void create()
{
        set("short", "天王殿");
        set("long", @LONG
這裡是少林寺的中殿天王殿。殿內香煙燎繞，幔角叮咚。香火比
前殿要旺盛的多。正前方供著個大肚子，似乎永遠都笑咪咪的彌勒佛。
四大天王分列兩旁，分執『風調雨順』。兩側香桌上擺滿了四季果蔬，
彌勒的身後站立的是韋馱。只見他金盔金甲，年輕英俊，威風凜凜，
雙手合十，金剛杵橫放腕上。左右兩邊各有一間偏殿。
LONG );
        set("exits", ([
                "east" : __DIR__"twdian1",
                "west" : __DIR__"twdian2",
                "southdown" : __DIR__"taijie",
                "north" : __DIR__"guangchang2",
        ]));
        set("objects",([
                CLASS_D("shaolin") + "/dao-guo" : 1,
                __DIR__"npc/xiang-ke" : 1,
        ]));
//        set("no_clean_up", 0);
        setup();
        replace_program(ROOM);
}
