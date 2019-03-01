inherit ROOM;

void create()
{
        set("short", "雜貨舖");
        set("long", @LONG
這裡是古村的雜貨舖，兩排長長的貨架上擺滿了玩家們所
需要的東西。老板是個胖胖的中年人，正在一邊精神的招呼著
客人，如果你需要什麼的話可以看看（輸入指令 list）。
LONG);
        set("exits", ([
                "north" : __DIR__"road2",
        ]));

        set("xinshoucun", 1);
        set("no_fight", 1);

        set("objects", ([
               __DIR__"npc/qianbo"  :  1,
        ]));
        setup();

        replace_program(ROOM);
}
