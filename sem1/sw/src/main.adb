-------------------------------------------------
--  Лабортаторна робота №1
--  Шкардибарда І. ІВ-82
--  Дата 01.11.2020
-------------------------------------------------
with Ada.Integer_Text_IO, Ada.Text_IO;
use Ada.Integer_Text_IO, Ada.Text_IO;
procedure Main is
   protected type SIMA(initial: Integer:=1; max: Integer:=1) is
      entry P;
      entry V;
   private
      current: integer:= initial;
      max_size: Integer:= max;
   end SIMA;
   protected body SIMA is
      entry P when current > 0 is
      begin
         current:= current - 1;
      end P;
      entry V when current < max_size is
      begin
         current:= current + 1;
      end V;
   end SIMA;
--  Create object of protected SIMA type with initial value 1 and max value 1
   Mon: SIMA(0, 1);
--  Declaration of tasks
   task T1;
   task body T1 is
   begin
      Mon.P;
      Put_Line("");
      for i in 0..4 loop
         put(1);
      end loop;
   end T1;
--  Task T2
   task T2;
   task body T2 is
   begin
      Put_Line("");
      for i in 0..4 loop
         put(2);
      end loop;
      Mon.V;
   end T2;
--  Task T3
   task T3;
   task body T3 is
   begin
      Mon.P;
      Put_Line("");
      for i in 0..4 loop
         put(3);
      end loop;
   end T3;
begin
   null;
end Main;
