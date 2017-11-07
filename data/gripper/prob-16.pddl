(define (problem gripper_16_balls)
   (:domain gripper_typed)
   (:objects
   rooma roomb - room
   ball16 ball15 ball14 ball13 ball12 ball11 ball10 ball9 ball8 ball7 ball6 ball5 ball4 ball3 ball2 ball1 - ball
   left right - gripper
   )
   (:init
          (at_robby rooma)
          (free left)
          (free right)
          (at_ball ball16 rooma)
          (at_ball ball15 rooma)
          (at_ball ball14 rooma)
          (at_ball ball13 rooma)
          (at_ball ball12 rooma)
          (at_ball ball11 rooma)
          (at_ball ball10 rooma)
          (at_ball ball9 rooma)
          (at_ball ball8 rooma)
          (at_ball ball7 rooma)
          (at_ball ball6 rooma)
          (at_ball ball5 rooma)
          (at_ball ball4 rooma)
          (at_ball ball3 rooma)
          (at_ball ball2 rooma)
          (at_ball ball1 rooma)
          )
   (:goal (and (at_ball ball16 roomb)
               (at_ball ball15 roomb)
               (at_ball ball14 roomb)
               (at_ball ball13 roomb)
               (at_ball ball12 roomb)
               (at_ball ball11 roomb)
               (at_ball ball10 roomb)
               (at_ball ball9 roomb)
               (at_ball ball8 roomb)
               (at_ball ball7 roomb)
               (at_ball ball6 roomb)
               (at_ball ball5 roomb)
               (at_ball ball4 roomb)
               (at_ball ball3 roomb)
               (at_ball ball2 roomb)
               (at_ball ball1 roomb))))
