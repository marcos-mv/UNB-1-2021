program GRID
    IMPLICIT none
    
    character, allocatable, dimension(:, :) :: matrix, result
    character, allocatable, dimension(:) :: packed
    logical, allocatable, dimension(:) :: mask
    
    integer :: i, j, fi, fj
    integer :: a, b
    logical :: need = .true.
    
    read(*, *) i, j
    
    fi = i
    fj = j
    
    allocate(matrix(i,j))
    allocate(packed(i*j))
    allocate(mask(i*j))
    
    !get matrix
    do a = 1, i
        read(*,*) matrix(a, :)
    end do
    
    ! print*, 'matrix: '
    ! !print matrix
    ! do a = 1, i
    !     print*, (matrix(a, b), b = 1, j)
    ! end do
    
    !need rows
    do a = 1, i
        need = .false.
        
        do b = 1, j
            if(matrix(a,b) == '#') then
                need = .true.
                exit
            end if
        end do
        
        if(.not. need) then
            fi = fi - 1
        end if
        
        do b = 1, j
            mask(b+(j*(a-1))) = need
        end do
    end do
    
    !need col
    
    do a = 1, j
        need = .false.
        
        do b = 1, i
            if(matrix(b,a) == '#') then
                need = .true.
                exit
            end if
        end do
        
        if(.not. need) then
        fj = fj-1
        end if
        
        do b = 1, i*j, j
            if (mask(b+(a-1)) .neqv. .false.) then
                mask(b+(a-1)) = need
            end if
        end do
    end do
    
    matrix = TRANSPOSE(matrix)
    packed = pack(matrix, .true.)
    
    !reshape
    allocate(result(fi, fj))
    packed = pack(packed, mask)
    result = reshape(packed,(/fi, fj/), (/'?'/), (/2,1/))
        
    ! print*, 'result: '
    
    !print result
    do a = 1, fi
        print*, (result(a, b), b = 1, fj)
    end do
    
    !deallocate
    deallocate(matrix)
    deallocate(mask)
    deallocate(result)
    
End Program GRID