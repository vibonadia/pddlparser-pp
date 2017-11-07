(define (problem robot-02)
	(:domain gripper)

	(:objects
		rooma roomb - room
		ball1 ball2 - ball
		left - gripper)

	(:init
		(free left) 
		(at-robby rooma)
		(at-ball ball1 rooma) 
		(at-ball ball2 rooma)
	)

	(:goal
		(and 
			(at-ball ball1 roomb)
			(at-ball ball2 roomb)
		)
	)
)
