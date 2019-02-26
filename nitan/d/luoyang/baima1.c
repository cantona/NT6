// Room: /d/luoyang/baima1.c
// Last modified by winder 2002.11.11

inherit  ROOM;

void  create  ()
{
        set("short",  "馬寺鐘聲");
        set("long",  @LONG
這裏是白馬寺的鐘樓。每當月白風清之夜，晨曦初露之時，殿內擊
磬撞鐘佛誦，鐘聲悠揚飄蕩，遠聞數裏，聽之使人心曠神怡。到明代，
寺內有口大鐵鐘，重約五千餘斤，鐘聲特別洪亮。據傳這口鐘與洛陽東
大街鐘樓上的一口鐘音律一致，可以共鳴。人們往往在聽到白馬寺鐘聲
的同時，緊接着洛陽城鐘樓上的鐘也響了，民間流傳着“東邊撞鐘西邊
響，西邊撞鐘東邊鳴”的佳話。
LONG);
        set("exits",  ([  /*  sizeof()  ==  2  */
                "west" : __DIR__"baimasi",
        ]));
        set("outdoors", "luoyang");
        set("no_clean_up", 0);
	set("coor/x", -6890);
	set("coor/y", 2160);
	set("coor/z", -10);
	setup();
        replace_program(ROOM);
}