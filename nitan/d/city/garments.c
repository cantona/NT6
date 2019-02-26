// Room: /city/garments.c

inherit ROOM;

void create()
{
	set("short", "成衣店");
        set("long", @LONG
這裏是揚州名媛貴婦常到之處，現在也擠得悽悽慘慘，脂粉橫飛。
因為這裏賣的時尚，一直是她們最熱衷的裝扮。店主是個很可人的小
女孩，你認真一看，頓時發現滿個店堂裏的女人加在一起，還不如她
靚麗。    店門口橫橫歪歪地寫着幾個大字(zi)。想來出自小滬手筆。
LONG );
	set("item_desc", ([
		"zi": "list 看，\"buy\" 買。\n",
	]));
	set("exits", ([
		"down" : "/d/city/zahuopu",
	]));
	set("objects", ([
		"/d/city/npc/zeng": 1,
	]));
	set("no_fight", 1);
	set("coor/x", 10);
	set("coor/y", -10);
	set("coor/z", 10);
	setup();
	replace_program(ROOM);
}