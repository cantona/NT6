// Room: /d/huanggong/qianqinggong.c

inherit ROOM;
#include <ansi.h>;
void create()
{
        set("short", "乾清宮");
        set("long", @LONG
這是皇上的寢宮. 乾清意為天下清寧平和. 皇上也常在這裡選派官
吏, 批閱文章, 召見臣下. 宮上橫匾“正大光明”, 是順治帝的親筆手
書, 以表明自己所作所為是正直大度和光明磊落的. 殿內四根柱子上懸
著兩幅楹聯, 一幅康熙大帝的御筆(kangxi), 另一幅是乾隆皇帝的御筆
(qianlong).
LONG
        );
        set("item_desc", ([
                "kangxi" : "
表正萬邦 慎厥身修思永
弘敷五典 無輕民事惟難
\n",
                "qianlong" : "
克寬克仁 皇建其有極
惟精惟一 道積于厥躬
\n",
        ]));
        set("exits", ([
                "west"      : __DIR__"huangqin",
                "east"      : __DIR__"duanning",
                "south"     : __DIR__"qianqingmen",
                "north"     : __DIR__"jiaotaidian",
                "southeast" : __DIR__"yushufang",
                "southwest" : __DIR__"jingshifang",
        ]));
        set("objects", ([
                __DIR__"npc/zhangkangnian": 1,
                __DIR__"npc/zhaoqixian": 1,
        ]));
	set("coor/x", -2810);
	set("coor/y", 7751);
	set("coor/z", 0);
	setup();
        replace_program(ROOM);
}