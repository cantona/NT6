//Edited by fandog, 01/31/2000

inherit ROOM;

void create ()
{
        set ("short", "琴館");
        set ("long", @LONG
這是一座飛檐高聳、畫棟雕樑的亭子，匾額上題“高山流水”四個
大字。亭中懸一字畫(zihua)。
LONG);
        set("item_desc", ([
                "zihua" : "這幅畫上畫的是伯牙“摔琴謝知音”的故事。畫中還題有四句詩：
                    摔碎瑤琴鳳尾寒
                    子期不在對誰彈
                    春風滿面皆朋友
                    欲覓知音難上難\n"
        ]));
        set("exits", ([
                "south" : __DIR__"qintai",
        ]));
  
	set("coor/x", -5080);
	set("coor/y", -1880);
	set("coor/z", 0);
	setup();
        replace_program(ROOM);
}