inherit ROOM;

void create()
{
        set("short", "雨花院");
        set("long", @LONG
相傳當年佛祖降臨天龍寺傳法時，漫天遍灑雨花石。後人以石建
院，即成此間玉花院。院中常年檀香四溢，令人心曠神怡。
LONG );
        set("exits", ([
                "west" : __DIR__"wuwujing",
                "south" : __DIR__"doumugong",
        ]));
        set("no_clean_up", 0);
        setup();
        replace_program(ROOM);
}