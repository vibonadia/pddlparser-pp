(define (problem griper-02)
	(:domain gripper)

	(:objects
		rooma roomb - room
		ball1 ball2 - ball
		left right - gripper)

	(:init
		(free left) 
		(free right)
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
