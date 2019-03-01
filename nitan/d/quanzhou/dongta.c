// Room: /d/quanzhou/dongta.c
// Last Modified by winder on May. 29 2001

inherit ROOM;

void create()
{
        set("short", "東塔");
        set("long", @LONG
東塔又名鎮國塔，完工于南宋淳佑十年，共耗時十二年。建塔時是
用堆土坡運石辦法，逐級建築上去的。它是一座渾體花崗石的仿木結構
的樓閣式建築，平面八方，五層五樓，頗為少見。塔座作須彌作形，塔
檐高翹，呈彎弧狀向外舒展。塔每層開四門設四龕，門外均伸出平座勾
欄。塔頂高托沃金銅葫蘆，映日閃閃發光。八條鐵鏈從塔頂上斜系于八
個角脊(jiaoji)。塔每層的門龕兩旁有武士、天王、金剛、羅漢等浮雕
計八十尊，神態各異。東塔須彌座束腰部分還有三十九幅難得一見的青
石浮雕佛傳圖。
LONG );
        set("outdoors", "quanzhou");
        set("no_clean_up", 0);
        set("item_desc", ([
                "jiaoji" : "每個角脊下還懸掛著小銅鐘，全塔共四十個，風一吹便叮當作響。\n",
        ]));
        set("exits", ([
                "west"   : __DIR__"yuetai",
        ]));
	set("coor/x", -910);
	set("coor/y", -7630);
	set("coor/z", 0);
	setup();
        replace_program(ROOM);
}