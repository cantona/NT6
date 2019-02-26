// Room: /d/quanzhou/lingshan.c
// Last Modified by winder on May. 29 2001

inherit ROOM;

void create()
{
        set("short", "靈山聖墓");
        set("long", @LONG
這是泉州東邊靈山的南麓，傳聞唐高祖武德年間，伊斯蘭教創始人
穆罕莫德派門徒三賢沙仕偈、四賢吾高仕來泉州傳教，卒葬於此。墓後
有一半圓形石築廊，上立有一中文碑記，乃「鄭和行香碑」(monument)。
這是著名航海家三寶太監鄭和第五次下西洋路過泉州，特至此墓行香禱
告，官府為之刻石記事的碑刻。
LONG );
        set("outdoors", "quanzhou");
        set("item_desc", ([
                "monument" :
"【欽差總兵太監鄭和，前往西洋忽魯漠斯等國公幹。永樂
十五年來此行香，望神靈保佑。鎮撫浦和日記立】\n",
        ]));
        set("exits", ([
                "south" : __DIR__"portroad1",
                "west"  : __DIR__"tumenshuiguan",
                "east"  : __DIR__"luoyangqiao",
        ]));
        set("no_clean_up", 0);
	set("coor/x", -870);
	set("coor/y", -7720);
	set("coor/z", 0);
	setup();
        replace_program(ROOM);
}