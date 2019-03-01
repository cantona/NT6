// Room: /yixing/nanxun.c
// Date: Nov.18 1998 by Winder

inherit ROOM;

void create()
{
        set("short", "南潯鎮");
        set("long", @LONG
湖州府自來文風甚盛，歷代才士輩出，樑時將中國字分為平上去入
四聲的沈約，元代書畫皆臻極品的趙孟兆都是湖州人氏。當地又以產筆
著名，湖州之筆，徽州之墨，宣城之紙，肇慶端溪之硯，文房四寶，天
下馳名。南潯鎮雖是湖州府的一個鎮，卻比尋常州縣還大，鎮上富戶極
多，著名的富室大族之中有一家姓莊。
LONG );
        set("outdoors", "yixing");
        set("no_clean_up", 0);
        set("exits", ([
                "north" : __DIR__"yixing",
        ]));
        set("objects", ([
                __DIR__"npc/seller" : 1,
        ]));
        set("coor/x", 230);
	set("coor/y", -1030);
	set("coor/z", 0);
	setup();
        replace_program(ROOM);
}