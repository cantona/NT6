// Room: /yangzhou/shizige.c
// Last Modified by Winder on Jul. 20 2000

inherit ROOM;

void create()
{
        set("short","十字閣");
        set("long",@LONG
十字閣南經曲廊連平台東北隅，閣呈“十”字形，高二層，層結五
頂，上覆鉻綠琉璃瓦和寶頂，中頂突出，似碧玉簪立。底層、樓層各面
皆圍以檻窗，其建築風格與熙春台和諧一致。底層面南兩柱，懸掛楹聯
(lian)。底層面北兩柱，懸掛杜甫劉禹錫集句楹聯(lian1)。
LONG );
        set("outdoors", "shouxihu");
        set("item_desc", ([
                "lian" : "
勝地重彩在紅藕花中綠楊蔭裡
簫聲依舊看長天一色朗月當空
\n",
                "lian1" : "
        碧        淺
        瓦        黃
        朱        輕
        甍        綠
        照        映
        城        樓
        郭        台
\n",
        ]));
        set("exits", ([
                "south" : __DIR__"pingtai5",
        ]));
        set("no_clean_up", 0);
        set("coor/x", -50);
        set("coor/y", 110);
        set("coor/z", 0);
        setup();
        replace_program(ROOM);
}