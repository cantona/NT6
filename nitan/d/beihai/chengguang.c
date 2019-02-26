// /d/beihai/chengguan.c
// Last Modified by winder on May. 22 2002

inherit ROOM;

void create()
{
        set("short", "承光殿");
        set("long", @LONG
這裏是主殿承光殿，位於團城中央，是康熙時有元代儀天殿基礎上
改建的。殿之方體結構為方形，重檐歇山頂，四面出抱廈，亦為歇山頂。
整個屋頂造型有如故宮之角樓狀。整個建築都用黃琉璃瓦，綠瓦剪邊。
殿內供玉觀音菩薩，雕琢精美潔白無暇，傳為高宗時西藏之貢物。殿東
側有一株高大蒼勁的油松，樹冠如蓋，乾隆帝曾封為“遮陰侯”。
LONG
        );
        set("exits", ([
                "east"  : __DIR__"zhaojing",
                "west"  : __DIR__"yanxiang",
                "north" : __DIR__"jingji",
                "south" : __DIR__"yuweng",
        ]));
        set("outdoors", "beihai");
        set("no_clean_up", 0);

        set("coor/x", -180);
        set("coor/y", 4050);
        set("coor/z", 0);
        setup();
        replace_program(ROOM);
}