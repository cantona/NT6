// Room: wangjianglou.c
// Date: Feb.14 1998 by Java

inherit ROOM;
void create()
{
        set("short", "望江樓");
        set("long", @LONG
望江樓又名崇麗閣。下兩層四角，上兩層八角，朱柱琉瓦，翹角
飛甍，雕樑畫棟，登臨其上，遠眺府南河，清風撲面，舟火穿梭，實
為勝景。樓的周遭，翠竹千莖朝天，每當雨霧氤氲，輕煙籠翠，竹籟
鳥音，動人心魄。樓前薛濤井，傳説因為薛濤漂洗一種紅色詩箋而流
芳千古： 無波古井因濤重，有色遺箋舉世珍。這也是這一才女的傳世
的唯一遺澤。
LONG );
        set("outdoors", "chengdu");
        set("exits", ([
            "northwest"  : __DIR__"eastroad3",
        ]));
        set("no_clean_up", 0);
        set("coor/x", -15190);
	set("coor/y", -1850);
	set("coor/z", 0);
	setup();
        replace_program(ROOM);
}