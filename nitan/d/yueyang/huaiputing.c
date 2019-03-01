// Room: /d/yueyang/huaiputing.c
// Last Modifyed by Winder on Dec. 4 2001

inherit ROOM;

void create()
{
        set("short", "懷甫亭");
        set("long", @LONG
“懷甫亭”是當年杜甫流落巴陵，貧窮潦倒，還為岳陽留下了《登
岳陽樓》等不朽詩篇(poem)。杜甫後來卒于岳陽。由此拾級西上即是岳
陽樓。
LONG );
        set("outdoors", "yueyang");
        set("no_clean_up", 0);
        set("item_desc", ([
                "poem" : "
                        登岳陽樓
　　
                 　　      　　杜甫

                 昔聞洞庭水，今上岳陽樓。
                 吳楚東南坼，乾坤日夜浮。
                 親朋無一字，老病有孤舟。
                 戎馬關山北，憑軒涕泗流。\n"
        ]));
        set("exits", ([
                "east"   : __DIR__"loumen",
                "westup" : __DIR__"yueyanglou1",
        ]));
	set("coor/x", -6230);
	set("coor/y", -3000);
	set("coor/z", 10);
	setup();
        replace_program(ROOM);
}