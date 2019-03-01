inherit ROOM;

void create()
{
        set("short", "石板大道");
        set("long", @LONG
這兒靠中州府不遠，路上行人來往不斷，你的眉頭也舒展
了開來，步子也越邁越大。北面就是中州府的南城門了。
LONG);
        set("exits", ([
                  "south" : __DIR__"toyy",
                  "north" : __DIR__"nanmeng",
        ]));

        set("outdoors", "zhongzhou");
        set("no_clean_up", 0);

        set("coor/x", -150);
        set("coor/y", -120);
        set("coor/z", 10);
        setup();
        replace_program(ROOM);
}