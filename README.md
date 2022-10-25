# wheel_tokyo_weili
使用 publish 傳遞 wheel_planner.msg進行控制機器人
topic名稱 /wheel/planner

distance_x y z(單位:公分)
決定機器人的移動方向跟移動距離

velocity_x y z(xy速度最快不要超過0.5，z最多不要超過1)
決定機器人的移動方向(持續給值會一直前進，給0會停止)

far_left far_right (bool)
true決定移動到最左邊或最右邊場地
------------------------------------------------------

使用 subscribe 接收 waitforidle.msg接收機器人移動狀態
topic名稱 /wheel/waitforidle

waitforidle(bool)
回傳 ture -> 機器人已完成指令動作，可以接收新指令
回傳 false -> 機器人正在進行動作，無法接收新指令