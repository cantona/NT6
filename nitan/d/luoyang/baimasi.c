// Room: /d/luoyang/baimasi.c
// Last modified by winder 2002.11.11

inherit  ROOM;

void  create  ()
{
        set("short",  "白馬寺");
        set("long",  @LONG
這裡就是著名的白馬寺，從寺廟點燃的眾多香火來看，這裡一直很
旺盛，每天來此上香的香客絡繹不絕。傳東漢明帝劉莊夜夢金神，從西
而來，飛繞殿庭。于是，派十八人出使西域，拜求佛法，在大月氏遇天
竺高僧攝摩騰、竺法蘭，得見佛經佛像。永平十年，漢使梵僧以白馬馱
載佛經佛像返洛，翌年建寺，遂以白馬為名。是佛教傳入中原後官府營
建的第一座佛教寺院。後世奉此寺為中華佛教的“祖庭”和“釋源”。
天王、大雄、接引、毗盧等殿建築完整，居然躲過了多年的戰亂。寺前
有一對石雕白馬，栩栩如生。
LONG);
        set("exits",  ([  /*  sizeof()  ==  2  */
                "east"      :  __DIR__"baima1",
                "southwest" :  __DIR__"road2",
        ]));
        set("outdoors", "luoyang");
        set("no_clean_up", 0);
	set("coor/x", -6900);
	set("coor/y", 2160);
	set("coor/z", -10);
	setup();
        replace_program(ROOM);
}