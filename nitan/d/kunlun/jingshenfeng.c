// Room: /d/kunlun/jingshenfeng.c 驚神峯
// Last Modified by winder on Nov. 14 2000

#include <ansi.h>
#include <room.h>
inherit ROOM;

void create()
{
        set("short","驚神峯"NOR);
        set("long",@long
折而向北，過了一嶺，只見古柏三把百餘章，皆挺直端秀，凌霄託
根樹旁，作花柏頂，燦若雲荼。走出十餘丈，只聽得琴聲之中雜有無數
鳥語，細細聽來，琴聲竟似和鳥語互相應答，間間關關，宛轉啼鳴。只
見三株大松樹下一個白衣男子背向而坐，膝上放着一張焦尾琴，整自彈
奏。他身周樹木上停滿了鳥雀，黃鶯，杜鵑，喜鵲，八哥，還有許多不
知其名的，和琴聲或一問一答，或齊聲和唱。
long );
        set("objects",([
                CLASS_D("kunlun")+"/hezudao" : 1,
        ]));
        set("exits", ([
                "south" : __DIR__"sanshengao",
        ]));
        set("outdoors", "kunlun");
        set("coor/x", -119980);
        set("coor/y", 40180);
        set("coor/z", 100);
        setup();
        replace_program(ROOM);
}