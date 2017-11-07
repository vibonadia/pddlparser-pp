(define (problem gripper_8_balls)
   (:domain gripper_typed)
   (:objects
   rooma roomb - room
   ball8 ball7 ball6 ball5 ball4 ball3 ball2 ball1 - ball
   left right - gripper
   )
   (:init
          (at_robby rooma)
          (free left)
          (free right)
          (at_ball ball8 rooma)
          (at_ball ball7 rooma)
          (at_ball ball6 rooma)
          (at_ball ball5 rooma)
          (at_ball ball4 rooma)
          (at_ball ball3 rooma)
          (at_ball ball2 rooma)
          (at_ball ball1 rooma)
          )
   (:goal
    (and
      (at_ball ball8 roomb)
               (at_ball ball7 roomb)
               (at_ball ball6 roomb)
               (at_ball ball5 roomb)
               (at_ball ball4 roomb)
               (at_ball ball3 roomb)
               (at_ball ball2 roomb)
               (at_ball ball1 roomb)))
)
