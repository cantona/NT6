// Room: /d/luoyang/luopu.c
// Last modified by winder 2002.11.11

inherit  ROOM;

void  create  ()
{
        set("short",  "洛浦秋風");
        set("long",  @LONG
洛河，桃李夾岸，楊柳成蔭，長橋卧波，一年四季風景如畫。尤在
是“金風消夏”“半月橫秋”時節，更具詩情畫意。三國時，曹子建説
他在河畔遇到一位神女，他就借題發揮寫了一篇《洛神賦》。號稱“初
唐四傑”的王勃、楊炯、盧照鄰、駱賓王曾徘徊洛濱，不忍離去。唐高
宗時，上官儀循着河堤，緩轡詠詩，洛賓景色之佳，可以想見。
LONG);
        set("exits",  ([  /*  sizeof()  ==  2  */
                "west"      : __DIR__"southgate",
                "southeast" : __DIR__"dukou1",
        ]));
        set("outdoors", "luoyang");
        set("no_clean_up", 0);
        set("coor/x", -490);
        set("coor/y", -30);
        set("coor/z", 0);
        setup();
        replace_program(ROOM);
}