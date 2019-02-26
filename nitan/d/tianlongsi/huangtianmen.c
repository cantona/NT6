inherit ROOM;

void create()
{
        set("short", "晃天門");
        set("long", @LONG
這是出入前後寺的必經之路。往南望去，可見後寺中亭台樓閣規
模宏大，構築精麗，宅地連雲，其氣勢之盛更勝於五台，普陀等諸處
佛門勝地的名山大寺。
LONG );
        set("outdoors","tianlongsi");
        set("exits", ([
                "south": __DIR__"yaotai",                            
                "west" : __DIR__"wulege",
                "east" : __DIR__"wuchangge",
        ]));
        set("no_clean_up", 0);
        setup();
        replace_program(ROOM);
}