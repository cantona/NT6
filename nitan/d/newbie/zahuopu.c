inherit ROOM;

void create()
{
        set("short", "雜貨鋪");
        set("long", @LONG
這裏是古村的雜貨鋪，兩排長長的貨架上擺滿了玩家們所
需要的東西。老闆是個胖胖的中年人，正在一邊精神的招呼着
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
