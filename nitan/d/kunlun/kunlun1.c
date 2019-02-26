inherit ROOM;
void create()
{
        set("short", "崑崙山麓");
        set("long", @LONG
這一帶樹木叢生，山石嶙峋，行走甚是不便，山上積雪更厚，道
路崎嶇，行走自是費力。轉過兩個山坡，進了一座大松林。林中松樹
都是數百年的老樹，枝柯交橫。
LONG );
        set("no_new_clean_up", 0);
        set("outdoors", "kunlun");
        set("exits", ([ /* sizeof() == 2 */
                "southwest" : __DIR__"kunlun2",
                "northeast" : __DIR__"klshanlu",

        ]));

        setup();
        replace_program(ROOM);
}