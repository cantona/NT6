// Room: /d/yueyang/xianglushan.c
// Last Modifyed by Winder on Dec. 4 2001

inherit ROOM;

void create()
{
        set("short", "香爐山");
        set("long", @LONG
香爐山，位於洞庭湖中的君山南面，方圓約四畝，山成穹廬形，山
上灌木叢生，青翠欲滴。四周峭壁如削，滔滔湖水後浪趕着前浪撞擊着
巖石，濺起一層層波光粼粼的水花，就好似它的腰間繫着一條白色的綿
帶，有時露出水面，有時隱沒在煙霧裏，如同一顆明珠嵌在波瀾壯闊的
洞庭湖上，給“八百里洞庭”和君山增添了絢麗多姿的色彩，真是意味
獨特，景趣迥然。
LONG );
        set("outdoors", "dongting");
        set("no_clean_up", 0);
        set("exits", ([
                "east"      : __DIR__"longwangmiao",
                "south"     : __DIR__"xiangchunting",
                "northdown" : __DIR__"yangeng2",
        ]));
        set("coor/x", -1800);
        set("coor/y", 2260);
        set("coor/z", 10);
        setup();
        replace_program(ROOM);
}