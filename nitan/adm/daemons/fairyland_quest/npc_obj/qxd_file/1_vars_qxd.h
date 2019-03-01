#define        YUN_LvNeed        20
// 運用技能需要的等級(cmd: yun)

#define        PFM_LvNeed        40
// 絕招需要的技能等級(cmd: pfm)

int time,deng,DENG_AMOUNT=7,MAX_HP=500,DENG_TIME=400;  // 標準設置為 300

// time,燈的數量（7個），玩家進入遊戲時最大氣，每個燈熄滅的時限（秒）
// 與下面之 extend_deng 值聯系，遊戲總時間為 deng_time 值的 10 倍。

int EXTEND_DENG = 3;

// 延長遊戲時間。當玩家進入遊戲時，先默算這幾輪；完了再開始滅燈。

string long_color=""HIC"",wait_over="no";
string longs="這是一個四四方方的小盒子，盒蓋透明，你能見到內裡有"+chinese_number(DENG_AMOUNT)+"個小點在散發著微弱的光芒。\n";

string *context1=({
    " ",
    "風",
    "我們輕靈而飄忽的國度",
    "它的寶物有著天馬之身 伸展之雙翼",
    "當你尋得它們",
    "你將能夠重見風之國度",
    "你將能夠領會它的啟示。",
});

string *context2=({
    " ",
    "雨",
    "我們柔和而聰慧的國度",
    "它的寶物有著晶瑩之淚 敏慧之心 和 靈巧之手",
    "當你尋得它們",
    "你將能夠重見雨之國度",
    "你將能夠領會它的啟示。",
});

string *context3=({
    " ",
    "雷",
    "我們勇敢而強壯的國度",
    "它的寶物有著神力之劍 點綴之石 和 容忍之鞘",
    "當你尋得它們",
    "你將能夠重見雷之國度",
    "你將能夠領會它的啟示。",
});

string *context4=({
    " ",
    "電",
    "我們勤勞而耐心的國度",
    "它的寶物最是難尋",
    "它時而隱藏  時而真現",
    "但它總改變不了自身的熒光。",
    "當你見到一顆寶石的模樣",
    "也許那就是你要尋找之物",
    "三顆寶石  將帶領你去體會",
    "古老的國度的秘密。",
});

void sing_song(int i, object me);
string singing="no";
string *songs;
int about_me_obj=0; // 0，表示未發放本人相關物品。
int start_checking=0; // 0，表示未啟動檢測程序。

void fighting();
void healing( object me );
mapping can_use_pfm( string fight_use, object me, object target );

