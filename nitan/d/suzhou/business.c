// Room: /d/datong/business.c

inherit WAREHOUSE;

void create()
{
        set("short", "蘇州商棧");
        set("long", @LONG
這裡就是著名的蘇州商棧，蘇州買賣商品的集散地，也是富商大
賈雲集之所，由蘇州商會控制。在蘇州大宗商品的買賣都要通過這裡
進行。門口掛著一塊木牌(sign)。
LONG );

        set("item_desc",([
        "sign" : "
list                    查看當地各種商品的價格。
shou <數量> 商品        收購一定數量的商品。
pao <數量> 商品         在本地拋售一定數量的商品。
fasong                  將你在本地的貨物發往其它的地點。
\n",
]));

        set("exits", ([ /* sizeof() == 2 */
                "south" : __DIR__"majiu",
]));

        // 初始貨物數量
        set("all_wares",([
        "rice" :   202500,     //1
        "wheat" :  364500,    //2   本地
        "corn" :   202500,     //3
        "ganzhe" : 202500,   //4
        "goober" : 202500,   //5
        "silk" :    40500,     //6
        "cloth" :  202500,    //7
        "zxiu" :    40500,     //8
        "iron" :   202500,     //9
        "tong" :   202500,     //10
        "diamand" : 40500,  //11
        "suis" :   364500,     //12  本地
        "gold" :    20250,      //13
        "silver" :  40500,   //14
        "picture" : 20250,   //15  
        "jxiu" :    20250,      //16
        "book" :    20250,      //17
        "vase" :    20250,      //18
        "harm" :   202500,     //19
        "guiy" :    40500,     //20
        "meat" :   202500,     //21
        "fish" :   202500,     //22
        "orange" : 202500,   //23
        "tea" :    202500,      //24
        "yye" :    202500,      //25
        "shen" :    20250,      //26
        "deer" :    20250,      //27
        "sdan" :    20250,      //28
        "bamboo" : 320000,   //29
        "pei" :     20250,       //30
        "hairpin" : 20250,   //31
        "qilin" :   20250,     //32  
        "guan" :    20250,      //33  
        "ddai" :    20250,      //34
        "mxia" :    20250,      //35
        "jade" :    20250,      //36
        "pearl" :   20250,     //37
        "bonsai" :  20250,    //38
        "spear" :  202500,    //39
        "sword" :  202500,    //40
        "blade" :  202500,    //41
        "shield" : 320000,   //42
        "jian" :        0,         //43  需要
        "armor" :    4050,     //44  需要
        "wood" :   202500,     //45
        "stone" :  320000,    //46
        "cansi" :   40500,    //47  
        "cotton" : 320000,   //48
        "salt" :   320000,     //49 
        "paper" :   40500,    //50
]));

        // 各類商品的價格指數
        set("kind_rate",([
        "wheat" :  76,     // 2  本地
        "suis" :  78,    //12  本地
       "jian" : 124,       //43  需要
       "armor" : 124,    //44  需要
]));
 
	set("coor/x", 1100);
	set("coor/y", -1030);
	set("coor/z", 0);
	setup();
}