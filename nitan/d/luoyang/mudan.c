// Room:  /d/luoyang/mudan.c
// Last modified by winder 2002.11.11

inherit  ROOM;

void  create  ()
{
        set("short",  "牡丹園");
        set("long",  @LONG
自古以來，洛陽墨客騷人云集，因此有“詩都”之稱，牡丹香氣四
溢，又有“花都”的美譽。宋代詩人歐陽修在《洛陽牡丹記》一文中寫
道：“洛陽地脈花最宜，牡丹尤為天下奇。”此句即道出了洛陽的地脈
使牡丹得天獨厚。洛陽牡丹以品種繁多，花色奇麗而名揚天下。故有“
洛陽牡丹甲天下”之名句流傳於世。這裏每年舉辦洛陽牡丹花會，人潮
湧動，蔚為壯觀。據説當年丐幫馬副幫主的夫人在此一笑傾國。
LONG);
        set("exits",  ([  /*  sizeof()  ==  2  */
                "southwest" : __DIR__"road5",
        ]));
        set("objects",  ([  /*  sizeof()  ==  2  */
                "/clone/flower/mudan/black1" : random(2),
                "/clone/flower/mudan/black2" : random(2),
                "/clone/flower/mudan/blue1" : random(2),
                "/clone/flower/mudan/blue2" : random(2),
                "/clone/flower/mudan/green1" : random(2),
                "/clone/flower/mudan/green2" : random(2),
                "/clone/flower/mudan/magenta1" : random(2),
                "/clone/flower/mudan/magenta2" : random(2),
                "/clone/flower/mudan/mudan1" : random(2),
                "/clone/flower/mudan/mudan2" : random(2),
                "/clone/flower/mudan/purple1" : random(2),
                "/clone/flower/mudan/purple2" : random(2),
                "/clone/flower/mudan/purple3" : random(2),
                "/clone/flower/mudan/red1" : random(2),
                "/clone/flower/mudan/red2" : random(2),
                "/clone/flower/mudan/red3" : random(2),
                "/clone/flower/mudan/red4" : random(2),
                "/clone/flower/mudan/white1" : random(2),
                "/clone/flower/mudan/white2" : random(2),
                "/clone/flower/mudan/white3" : random(2),
                "/clone/flower/mudan/white4" : random(2),
                "/clone/flower/mudan/yellow1" : random(2),
                "/clone/flower/mudan/yellow2" : random(2),
        ]));
        set("outdoors", "luoyang");
        set("no_get_from", 1);
        set("no_clean_up", 0);
	set("coor/x", -6980);
	set("coor/y", 2260);
	set("coor/z", 0);
	setup();
        replace_program(ROOM);
}