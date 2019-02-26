// Room: /d/yanping/meishanpo.c
// Date: Sep 28, 2002  Winder

inherit ROOM;

void create()
{
        set("short", "梅山坡");
        set("long", @LONG
梅山坡上遍植梅花，漫坡盈野，一到花季，但見羣芳綻放，萬物
回春，如朝陽遍灑，璀璨無邊。“梅山朝暉”位列延平八景之一，年
年吸引無數文人騷客，揮金擲酒，共享花時。
LONG );
        set("exits", ([
                "westup"   : __DIR__"zhouxue",
                "northup"  : __DIR__"beimenling",
                "eastdown" : __DIR__"dongmen",
        ]));
        set("outdoors", "yanping");
        set("no_clean_up", 0);
        set("coor/x", 1480);
        set("coor/y", -6170);
        set("coor/z", 20);
        setup();
        replace_program(ROOM);
}