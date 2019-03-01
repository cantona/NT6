// Room: /d/wuyi/yunwo.c
// Last modified by Winder on Mar.20.2002

inherit ROOM;

void create()
{
        set("short", "雲窩");
        set("long", @LONG
雲窩位于第五曲北。周圍蒼崖聳立，碧水回流，修竹叢生，怪石橫
陳。雲窩前有一黝黑如巨象的“鐵象石”，石前為下雲窩，石後為上雲
窩。大小洞穴十余處。每當冬春時節，一早一晚，從洞裡冒出縷縷淡淡
雲霧，在峰石之間來回飄盪，舒卷自如，變幻莫測，自古此處邊式道士
方家潛度所在。
LONG );
        set("outdoors", "wuyi");
        set("no_clean_up", 0);
        set("exits", ([
                "west"   : __DIR__"fuhuyan",
                "north"  : __DIR__"jiesunfeng",
                "south"  : __DIR__"5qu",
                "eastup" : __DIR__"yinpingfeng",
        ]));
        set("no_clean_up", 0);
        set("coor/x", 1360);
        set("coor/y", -5010);
        set("coor/z", 10);
        setup();
        replace_program(ROOM);
}
