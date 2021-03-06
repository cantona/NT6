// Room: /d/songshan/tieliang.c
// Last Modified by Winder on Jul. 15 2001

inherit ROOM;

void create()
{
        set("short", "鐵樑峽");
        set("long", @LONG
由此上山，山路越發險竣。鐵樑峽右側盡是怪石，而左邊則為萬仞
深谷，渺不見底。隔着峽谷，青岡峯環抱青岡坪，向上是嵩山主峯的山
路。
    登高遠眺石羊關，隱隱可見“玉溪垂釣”(jing)處。
LONG );
        set("item_desc", ([
                "jing" : "
    石羊關東，潁水下源，有一小湖，方可數畝，名曰“玉溪”。溪南
有泉水數處，從平地噴出，騰湧而上，高近七尺，好似一串串的珍珠，
人稱“飛玉泉”。玉溪湖中，有一巨石，約三丈見方，有三分有二沒於
水中，遊人可登石穩坐，執竿釣魚。據傳説這是上古時代的隱士許由和
巢父二人釣魚的地方。相傳姜太公是個有遠見卓越的人，他不願在朝作
官，經常隱居於玉溪湖畔，坐在巨石上釣魚。他用的釣魚鈎是直的。終
日坐在石上，一邊釣一邊説：“願上鈎者上鈎，不願上鈎者順水而去”。
他的妻子天天送飯，總不見他釣到魚。等太公吃飯時，其妻發現魚鈎是
直的，偷將直鈎捏個彎鈎。太公飯罷，照常釣魚，不料很快釣出魚來，
他隨手又把魚拋入溪中。傷魚帶血而下，官兵發現太公居位上游，即速
稟報給周文王得知，文王親迎太公入朝。“玉溪垂釣”即由此而得名。
    古人《釣魚台》詩云：
                  台前落日寒鴻哀，台下西風潁水來。
                  一曲渝浪秋色景，白雲紅葉好登台。
",
        ]));
        set("exits", ([
                "down"    : __DIR__"luyasi",
                "northup" : __DIR__"shandao5",
        ]));
        set("objects", ([
                __DIR__"npc/xiazi" : random(3)+1,
        ]));
        set("outdoors", "songshan");
        set("coor/x", -20);
        set("coor/y", 810);
        set("coor/z", 40);
        setup();
        replace_program(ROOM);
}