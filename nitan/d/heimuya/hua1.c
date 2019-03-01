//ROOM: hua1.c

inherit ROOM;

void create()
{
        set("short", "花園");
        set("long", @LONG
這是一個極精致的小花園。園中，紅梅綠竹，青鬆翠柏，布置得
頗具匠心，往西去是一片青草地。
LONG );
        set("exits", ([
            "west" : __DIR__"grass2",
        ]));
        set("no_clean_up", 0);
        setup();
        replace_program(ROOM);
}