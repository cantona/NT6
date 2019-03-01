// nature.c
// by Find.
// 此特性標準 room 和 npc 裡已經繼承，
// 區域編程可以直接引用這些函數。

// 這個函數返回當前遊戲的年度數.
int query_year()
{
        object ob = find_object(NATURE_D);

        if(!ob) write("error: Can't find NATURE_D.\n");

        return ob->query_year();
}

/* 這個函數返回當前遊戲的季節.
 * 返回值 "1" : 春季.
 * 返回值 "2" : 夏季.
 * 返回值 "3" : 秋季.
 * 返回值 "4" : 冬季.
 */
int query_season()
{
        object ob = find_object(NATURE_D);

        if(!ob) write("error: Can't find NATURE_D.\n");

        return ob->query_season();
}

// 這個函數返回當前遊戲的月份數(1 - 12).
int query_month()
{

        int month,day;
        object ob = find_object(NATURE_D);

        if(!ob) write("error: Can't find NATURE_D.\n");

        sscanf( NATURE_D->query_month(),"month %d:day %d",month,day);

        return month;
}

// 這個函數返回現在是此月中的第幾天。
int query_day_in_month()
{
        int month,day;
        object ob = find_object(NATURE_D);

        if(!ob) write("error: Can't find NATURE_D.\n");

        sscanf( NATURE_D->query_month(),"month %d:day %d",month,day);

        return day;
}

// 這個函數返回當前處于一年中的第幾天(1 - 365).
int query_day(int *month_day)
{
        object ob = find_object(NATURE_D);

        if(!ob) error("error: Can't find NATURE_D.\n");

        return ob->query_day(month_day);
}

// 這個函數返回當前的天氣狀況.
// 目前的狀況有: clear 晴,snow 雪,wind 風,fog 霧,cloudy 雲,
// cloudy 進展到最後就是雨.
string weather_now()
{
        string effect,degree;

        object ob = find_object(NATURE_D);

        if(!ob) write("error: Can't find NATURE_D.\n");

        sscanf( ob->query_weather(),"%s %s",effect,degree);

        return effect;
}

// 這個函數返回當前的天氣狀況進展的程度.
// "begain" : 剛剛開始,不明顯.
// "last"   : 開始加重了.
// "finish" : 非常嚴重,但也進展到最後了.
// 比如 "cloudy" 如果進展到 "finish" 就要下雨了.
// "clear" 的程度沒有意義.就返回一個 "now".
// 如果您所要做的效果需要精確的採集到當前的天氣狀況.
// 就需要結合狀況、程度和季節綜合的判斷。
string weather_degree()
{
        string effect,degree;

        object ob = find_object(NATURE_D);

        if(!ob) write("error: Can't find NATURE_D.\n");

        sscanf( ob->query_weather(),"%s %s",effect,degree);

        return degree;

}

// 這個函數判斷目前是白天還是黑夜.
// 返回值為 "1" : 白天.
// 返回值為 "0" : 黑夜.
int is_day()
{
        string day_night;
        int time;
        object ob = find_object(NATURE_D);

        if(!ob) write("error: Can't find NATURE_D.\n");

        sscanf( ob->day_or_night(),"%s %d",day_night,time);

        return (day_night == "day");
}

// 這個函數返回晝夜更替的一些詳細信息.
// 返回值是一個字串,格式為: "day_or_night last_time".
// day_or_night 為一個字串,值為 "day" 或者 "night" 反
// 映目前是白天還是黑夜.
// last_time 是一個 int,反映的是距離晝夜更替所剩的時間.
// 比如返回值 "day 280" 說明目前是白天,距離夜晚還有280秒.
// 中間以一個空格隔開.
string day_night()
{
        object ob = find_object(NATURE_D);

        if(!ob) write("error: Can't find NATURE_D.\n");

        return ob->day_or_night();
}

// 這個函數返回目前為一天中的第幾分鐘.
int query_time()
{
        object ob = find_object(NATURE_D);

        if(!ob) write("error: Can't find NATURE_D.\n");

        return ob->query_current_time();
}