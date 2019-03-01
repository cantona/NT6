//Edited by fandog, 01/31/2000

inherit ROOM;
void create ()
{

        set ("short", "空屋");
        set ("long", @LONG
室中空空洞洞，除了一桌、一椅、一床之外，什麼東西也沒有。床
上掛著一頂夏布白帳子，一床薄被，一個布枕，床腳邊放著一雙青布女
鞋。只是這一雙女鞋，才顯得這房間原為一個女子所住。
LONG);

        set("exits", ([ 
                "west" : __DIR__"loudao",
                "south": __DIR__"kongwu2",
        ]));
  
        set("no_clean_up", 0);
        set("coor/x", -7110);
	set("coor/y", -2090);
	set("coor/z", 10);
	setup();
        replace_program(ROOM);
}