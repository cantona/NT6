// Room: /d/huanggong/yangxin.c

inherit ROOM;

void create()
{
        set("short", "養心殿");
        set("long", @LONG
養心殿是皇帝居住和處理日常政務的地方. 在北牆上懸掛著一個匾
額(bian), 寶座屏風上有乾隆御筆題字(zi). 東暖閣豎著聖祖聖訓和世
宗聖訓各八條. 西暖閣裡,  "勤政親賢" 橫幅下, 是一幅世宗的御筆楹
聯(lian). 這是也一些官員在選拔, 調動前被帶來見聖的地方. 書架上
存放著一些關于老皇帝治理國家的經驗、教訓的書籍, 是供小皇帝學習
的.
LONG
        );
        set("exits", ([ /* sizeof() == 2 */
                "east"  : __DIR__"yuehua",
        ]));
        set("item_desc", ([ /* sizeof() == 2 */
                "bian"  : "
中正仁和\n\n",
                "zi"  : "
保泰常欽若
調元益懋哉\n\n",
                "lian"  : "
惟以一人治天下
豈為天下奉一人\n\n",
        ]));
        set("no_clean_up", 0);

	set("coor/x", -2830);
	set("coor/y", 7741);
	set("coor/z", 0);
	setup();
        replace_program(ROOM);
}