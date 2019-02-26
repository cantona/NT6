// lhqlwch.c

inherit ROOM;

void create()
{
        set("short", "練武場");
        set("long", @LONG
走進了烈火旗的練武場，發現練武的教眾們並不是在相互切磋武
功，而是穿戴着特製的防火護具，在學習使用火具和瞄準。火具中噴
出黝黑的原油，見火即燃，威力無比。
LONG );
        set("exits", ([
                "east" : __DIR__"lhqyuan",
                "west" : __DIR__"szchang",
        ]));
        set("outdoors", "mingjiao");
        set("no_clean_up", 0);
        setup();
        replace_program(ROOM);
}