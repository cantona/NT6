// /d/yanziwu/muzhuang.c

inherit ROOM;

void create()
{
        set("short", "木樁");
        set("long", @LONG
煙波浩淼的大湖上，水天一色，多麼美麗的地方，在這兒練功怎
能不事半功倍呢。
LONG );
        set("outdoors", "yanziwu");
        set("no_clean_up", 0);
        setup();
        replace_program(ROOM);
}