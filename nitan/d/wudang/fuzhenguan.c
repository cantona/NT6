inherit ROOM;

void create()
{
        set("short", "復真觀五層樓");
        set("long", @LONG
復真觀五層樓構造奇特，其間有十二根樑枋交叉重疊，下面僅用
一柱支撐，即有名的「一柱十二樑」。在這裡俯瞰群山煙雲迷離，遠
望金頂，一柱擎天，為觀景勝地。
LONG );
        set("exits", ([
                "west"     : __DIR__"taizipo",
        ]));
        set("no_clean_up", 0);
        set("coor/x", -360);
        set("coor/y", -240);
        set("coor/z", 60);
        setup();
        replace_program(ROOM);
}