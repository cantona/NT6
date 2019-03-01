// Room: /yangzhou/jicuixuan.c
// Last Modified by Winder on Jul. 20 2000
#include <ansi.h>;
inherit ROOM;

void create()
{
        set("short","積翠軒");
        set("long",@LONG
積翠軒，面南三楹，是一個曲廊、山石水池、花樹翠竹組成精巧庭
院，上懸匾額，外柱懸掛集句楹聯(lian)。東面是一道曲廊，曲廊南端
通半亭，亭名“半青”。過半亭達中院，南為“林香榭”，外柱懸掛楹
聯(lian1) 。于榭前臨水平台欣賞白塔麗姿，可得“白塔晴雲”命意旨
趣。北為“花南水北之堂”，外柱懸掛李嶠、許渾集詩楹聯(lian2)。
兩堂以廊相連。
LONG );
        set("outdoors", "shouxihu");
        set("item_desc", ([
                "lian" : HIG"
        壘        當
        石        軒
        通        暗
        溪        綠
        水        筠
\n"NOR,
                "lian1" : HIG"
        名        仙
        園        塔
        依        儷
        綠        雲
        水        莊
\n"NOR,
                "lian2" : HIG"
        別        前
        業        軒
        臨        枕
        青        大
        甸        河
\n"NOR,
        ]));
        set("exits", ([
                "northwest" : __DIR__"baitaqingyun",
        ]));
        set("no_clean_up", 0);
        set("coor/x", -10);
        set("coor/y", 90);
        set("coor/z", 0);
        setup();
        replace_program(ROOM);
}